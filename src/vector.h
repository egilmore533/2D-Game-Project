#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <SDL.h>


/** @brief	A macro that defines degrees to radians from DJ's MoGUL types file. */
#define ERIC_DEGTORAD	 0.017453292519943295769236907684886

/**
* @brief a simple 2d vector structure
*/
typedef struct
{
	float x,y;	/**<the x and y component of the vector */
}Vect2d;

/**
* @brief a simple 3d vector structure
*/
typedef struct
{
	union {
			float x;	/**<the x component of the vector */
			float r;	/**<the red component of the color */
	};
	union {
		float y;	/**<the y component of the vector */
		float g;	/**<the green component of the color */
	};
	union {
		float z;	/**<the z component of the vector */
		float b;	/**<the blue component of the color */
	};
}Vect3d;

/**
* @brief a simple 4d vector structure
*/
typedef struct
{
	union {
		float x;	/**<the x component of the vector */
		float r;	/**<the red component of the color */
	};
	union {
		float y;	/**<the y component of the vector */
		float g;	/**<the green component of the color */
	};
	union {
		float z;	/**<the z component of the vector */
		float b;	/**<the blue component of the color */
	};
	union {
		float w;	/**<the w component of the vector */
		float a;	/**<the alpha component of the color */
	};
}Vect4d;

/**
 * @brief	A macro that adds two vect2d together.
 * @param	a  	The first vect2d to add.
 * @param	b  	The second vect2d to add.
 * @param	sum	The resulting sum of the two vect2ds in a vect2d.
 */
#define vect2d_add(a,b,sum) (sum.x=a.x+b.x, sum.y=a.y+b.y)

/**
 * @brief	A macro that adds two vect3d together.
 * @param	a  	The first vect3d to add.
 * @param	b  	The second vect3d to add.
 * @param	sum	The resulting sum of the two vect3d in a vect3d.
 */
#define vect3d_add(a,b,sum) (sum.x=a.x+b.x, sum.y=a.y+b.y, sum.z=a.z+b.z)

/**
 * @brief	A macro that adds two vect4d together.
 * @param	a  	The first vect4d to add.
 * @param	b  	The second vect4d to add.
 * @param	sum	The resulting sum of the two vect4d in a vect4d.
 */
#define vec4d_add(a,b,sum) (sum.x=a.x+b.x, sum.y=a.y+b.y, sum.z=a.z+b.z, sum.w=a.w+b.w)

/**
 * @brief	A macro that mutiplies two vect2ds together and puts the product inside a vect2d.
 * @param	a   	The first vect2d to mutiply.
 * @param	b   	The second vect2d to mutiply.
 * @param	prod	The resulting product of the two vect2ds in a vect2d.
 */
#define vect2d_mutiply(a,b,prod) (prod.x=a.x*b.x, prod.y=a.y*b.y)

/**
 * @brief	A macro that mutiplies two vect3d together and puts the product inside a vect3d.
 * @param	a   	The first vect3d to mutiply.
 * @param	b   	The second vect3d to mutiply.
 * @param	prod	The resulting product of the two vect3d in a vect3d.
 */
#define vect3d_mutiply(a,b,prod) (prod.x=a.x*b.x, prod.y=a.y*b.y, prod.z=a.z*b.z)

/**
 * @brief	A macro that mutiplies two vect4ds together and puts the product inside a vect4d.
 * @param	a   	The first vect4d to mutiply.
 * @param	b   	The second vect4d to mutiply.
 * @param	prod	The resulting product of the two vect4d in a vect4d.
 */
#define vect4d_mutiply(a,b,prod) (prod.x=a.x*b.x, prod.y=a.y*b.y, prod.z=a.z*b.z, prod.w=a.w*b.w)

/**
 * @brief	A macro that sets a vect2d's constraints to given floats.
 * @param	vect	The vect to set.
 * @param	a   	The x coordinate of the vect2d.
 * @param	b   	The y coordinate of the vect2d.
 */
#define vect2d_set(vect, a,b) (vect.x=(a), vect.y=(b))

/**
 * @brief	A macro that sets a vect3d's constraints to given floats.
 * @param	vect	The vect to set.
 * @param	a   	The x coordinate of the vect3d.
 * @param	b   	The y coordinate of the vect3d.
 * @param	c   	The z coordinate of the vect3d.
 */
#define vect3d_set(vect, a,b,c) (vect.x=(a), vect.y=(b), vect.z=(c))

/**
 * @brief	A macro that sets a vect2d's constraints to given floats.
 * @param	vect	The vect to set.
 * @param	a   	The x coordinate of the vect4d.
 * @param	b   	The y coordinate of teh vect4d.
 * @param	c   	The z coordinate of the vect4d.
 * @param	d   	The w coordinate of the vect4d.
 */
#define vect4d_set(vect, a,b,c,d) (vect.x=(a), vect.y=(b), vect.z=(c), vect.w=(d))

/**
 * @brief	A macro that takes a vect2d and negates it.
 * @param	neg 	The resulting negative vect2d.
 * @param	vect	The vect2d to be negated.
 */
#define vect2d_negate(neg,vect) (neg.x=(-vect.x), neg.y=-(vect.y))

/**
 * @brief	A macro that takes a vect3d and negates it.
 * @param	neg 	The resulting negative vect3d.
 * @param	vect	The vect3d to be negated.
 */
#define vect3d_negate(neg,vect) (neg.x=(-vect.x), neg.y=(-vect.y), neg.z=(-vect.z))

/**
 * @brief	A macro that takes a vect4d and negates it.
 * @param	neg 	The resulting negative vect4d.
 * @param	vect	The vect4d to be negated.
 */
#define vect4d_negate(neg,vect) (neg.x=(-vect.x), neg.y=(-vect.y), neg.z=(-vect.z), neg.w=(-vect.w))

/**
 * @brief	A macro that takes a vect2d and a factor to mutiply the vect2d by
 * @param	vect  	The resulting vect2d.
 * @param	vectIn	The vect2d in.
 * @param	factor	The factor that the vector is being scaled by.
 */
#define vect2d_scale(vect,vectIn,factor) (vect.x=vectIn.x*factor, vect.y=vectIn.y*factor)

/**
 * @brief	A macro that takes a vect3d and a factor to mutiply the vect3d by.
 * @param	vect  	The resulting vect3d.
 * @param	vectIn	The vect3d in.
 * @param	factor	The factor that the vector is being scaled by.
 */
#define vect3d_scale(vect,vectIn,factor) (vect.x=vectIn.x*factor, vect.y=vectIn.y*factor, vect.z=vectIn.z*factor)

/**
 * @brief	A macro that takes a vect4d and a factor to mutiply the vect4d by.
 * @param	vect  	The resulting vect4d.
 * @param	vectIn	The vect4d in.
 * @param	factor	The factor that the vect4d is being scaled by.
 */
#define vect4d_scale(vect,vectIn,factor) (vect.x=vectIn.x*factor, vect.y=vectIn.y*factor, vect.z=vectIn.z*factor, vect.w=vectIn.w*factor)


void vect2d_normalize (Vect2d *vect);
void vect3d_normalize (Vect3d *vect);
void vect4d_normalize (Vect4d *vect);

/**
 * @brief	Vect 3D cross product because I learned it from Jimmy.
 * @param [in,out]	out	If non-null, the resulting vect from the cross product.
 * @param	v1		   	The first Vect3d.
 * @param	v2		   	The second Vect3d.
 */
void vect3d_cross_product(Vect3d *out, Vect3d v1, Vect3d v2);

/**
 * @brief	Vect 3D angle to vector.
 * @param	angles		  	The angles.
 * @param [in,out]	foward	If non-null, the foward.
 * @param [in,out]	right 	If non-null, the right.
 * @param [in,out]	up	  	If non-null, the up.
 */
void vect3d_angle_to_vector(Vect3d angles, Vect3d *foward, Vect3d *right, Vect3d *up);

float vect2d_get_length(Vect2d vect);
float vect3d_get_length(Vect3d vect);
float vect4d_get_length(Vect4d vect);

void vect2d_normalize(Vect2d *vect);
void vect3d_normalize(Vect3d *vect);
void vect4d_normalize(Vect3d *vect);


void vect3d_angle(Vect3d *out, float radians);
void vect4d_angle(Vect4d *out, float radians);

void vect3d_rotate_about_x(Vect3d *vect, float angle);

/**
 * @brief	check if two rectangles intersect
 * @param	a	The SDL_Rect to process.
 * @param	b	The SDL_Rect to process.
 * @return  a flag true or false.
 */
int rect_intersect(SDL_Rect a, SDL_Rect b);

SDL_Rect rect(int x, int y, int w, int h);

#endif
