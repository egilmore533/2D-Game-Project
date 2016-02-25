#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "sprite.h"
#include "entity.h"
#include "simple_logger.h"

struct
{
	Uint32 state;
	Uint32 shown;
	Uint32 frame;
	Uint16  x, y;
}Mouse;

SDL_Surface *buffer; /*pointer to the background image buffer*/
SDL_Surface *videobuffer; /*pointer to the draw buffer*/
SDL_Rect Camera; /*x & y are the coordinates for the background map, w and h are of the screen*/
Sprite *Msprite;
Uint32 NOW;					/*the current time since program started*/

static SDL_Window   *   g_graphics_main_window = NULL;
static SDL_Renderer *   g_graphics_renderer = NULL;
static SDL_Texture  *   g_graphics_texture = NULL;
static SDL_Surface  *   g_graphics_surface = NULL;
static SDL_Surface  *   g_graphics_temp_buffer = NULL;

/*timing*/
static Uint32 g_graphics_frame_delay = 30;
static Uint32 g_graphics_now = 0;
static Uint32 g_graphics_then = 0;
static Uint8 g_graphics_print_fps = 1;
static float g_graphics_fps = 0; 

/*some data on the video settings that can be useful for a lot of functions*/
static int g_bitdepth;
static Uint32 g_rmask;
static Uint32 g_gmask;
static Uint32 g_bmask;
static Uint32 g_amask;

void g_graphics_close();

void Init_Graphics(
	char *windowName,
    int viewWidth,
    int viewHeight,
    int renderWidth,
    int renderHeight,
    float bgcolor[4],
    int fullscreen)
{
    Uint32 flags = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Unable to initilaize SDL system: %s",SDL_GetError());
        return;
    }
    atexit(SDL_Quit);
    if (fullscreen)
    {
        if (renderWidth == 0)
        {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        else
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }
    }
    g_graphics_main_window = SDL_CreateWindow(windowName,
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             renderWidth, renderHeight,
                             flags);

    if (!g_graphics_main_window)
    {
        printf("failed to create main window: %s",SDL_GetError());
        g_graphics_close();
        return;
    }
    
    g_graphics_renderer = SDL_CreateRenderer(g_graphics_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!g_graphics_renderer)
    {
        printf("failed to create renderer: %s",SDL_GetError());
        g_graphics_close();
        return;
    }
    
    SDL_SetRenderDrawColor(g_graphics_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_graphics_renderer);
    SDL_RenderPresent(g_graphics_renderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(g_graphics_renderer, renderWidth, renderHeight);

    g_graphics_texture = SDL_CreateTexture(
        g_graphics_renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        renderWidth, renderHeight);
    if (!g_graphics_texture)
    {
        printf("failed to create screen texture: %s",SDL_GetError());
        g_graphics_close();
        return;
    };
    
    SDL_PixelFormatEnumToMasks(SDL_PIXELFORMAT_ARGB8888,
                                    &g_bitdepth,
                                    &g_rmask,
                                    &g_gmask,
                                    &g_bmask,
                                    &g_amask);

    
    g_graphics_surface = SDL_CreateRGBSurface(0, renderWidth, renderHeight, g_bitdepth,
                                        g_rmask,
                                    g_gmask,
                                    g_bmask,
                                    g_amask);
    buffer = SDL_CreateRGBSurface(0, renderWidth, renderHeight, g_bitdepth,
                                                 g_rmask,
                                                 g_gmask,
                                                 g_bmask,
                                                 g_amask);    
    if (!g_graphics_surface)
    {
        printf("failed to create screen surface: %s",SDL_GetError());
        g_graphics_close();
        return;
    }
        
    atexit(g_graphics_close);
    printf("graphics initialized\n");
}

void g_graphics_render_surface_to_screen(SDL_Surface *surface,SDL_Rect srcRect,int x,int y)
{
    SDL_Rect dstRect;
    SDL_Point point = {1,1};
    int w,h;
    if (!g_graphics_texture)
    {
        printf("g_graphics_render_surface_to_screen: no texture available");
        return;
    }
    if (!surface)
    {
        printf("g_graphics_render_surface_to_screen: no surface provided");
        return;
    }
    SDL_QueryTexture(g_graphics_texture,
                     NULL,
                     NULL,
                     &w,
                     &h);
    /*check if resize is needed*/
    if ((surface->w > w)||(surface->h > h))
    {
        SDL_DestroyTexture(g_graphics_texture);
        g_graphics_texture = SDL_CreateTexture(g_graphics_renderer,
                                                   g_graphics_surface->format->format,
                                                   SDL_TEXTUREACCESS_STREAMING, 
                                                   surface->w,
                                                   surface->h);
        if (!g_graphics_texture)
        {
            printf("g_graphics_render_surface_to_screen: failed to allocate more space for the screen texture!");
            return;
        }
    }
    SDL_SetTextureBlendMode(g_graphics_texture,SDL_BLENDMODE_BLEND);        
    SDL_UpdateTexture(g_graphics_texture,
                      &srcRect,
                      surface->pixels,
                      surface->pitch);
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
    SDL_RenderCopy(g_graphics_renderer,
                     g_graphics_texture,
                     &srcRect,
                     &dstRect);
}


void ResetBuffer()
{
    
}

void FrameDelay()
{
	Uint32 diff;
	g_graphics_then = g_graphics_now;
    g_graphics_now = SDL_GetTicks();
    diff = (g_graphics_now - g_graphics_then);
    if (diff < g_graphics_frame_delay)
    {
        SDL_Delay(g_graphics_frame_delay - diff);
    }
    g_graphics_fps = 1000.0/MAX(SDL_GetTicks() - g_graphics_then,0.001);
    if (g_graphics_print_fps)
    {
        slog("FPS: %f",g_graphics_fps);
    }
}

void NextFrame()
{
  SDL_RenderPresent(g_graphics_renderer);
  FrameDelay(); 
}

void g_graphics_close()
{
    if (g_graphics_texture)
    {
        SDL_DestroyTexture(g_graphics_texture);
    }
    if (g_graphics_renderer)
    {
        SDL_DestroyRenderer(g_graphics_renderer);
    }
    if (g_graphics_main_window)
    {
        SDL_DestroyWindow(g_graphics_main_window);
    }
    if (g_graphics_surface)
    {
        SDL_FreeSurface(g_graphics_surface);
    }
    if (g_graphics_temp_buffer)
    {
        SDL_FreeSurface(g_graphics_temp_buffer);
    }
    g_graphics_surface = NULL;
    g_graphics_main_window = NULL;
    g_graphics_renderer = NULL;
    g_graphics_texture = NULL;
    g_graphics_temp_buffer = NULL;
}

/*mouse handling functions*/
/*this only handles the drawing and animation of.  Assuming you have a 16 by 16  tiled sprite sheet.  This will not handle input*/
void InitMouse()
{

  Msprite = sprite_load("images/mouse.png",16, 16, 16);
  if(Msprite == NULL)fprintf(stdout,"mouse didn't load: %s\n", SDL_GetError());
  Mouse.state = 0;
  Mouse.shown = 0;
  Mouse.frame = 0;
}

    /*draws to the screen immediately before the blit, after all
     it wouldn't be a very good mouse if it got covered up by the
     game content*/
void DrawMouse()
{
  int mx,my;
  Vect2d m;
  SDL_GetMouseState(&mx,&my);
  vect2d_set(m, mx, my);
  if(Msprite != NULL) sprite_draw(Msprite, Mouse.frame, m);
  Mouse.frame = (Mouse.frame + 1)%16;
 Mouse.x = mx;
 Mouse.y = my;
}

SDL_Renderer *get_renderer()
{
	return g_graphics_renderer;
}

