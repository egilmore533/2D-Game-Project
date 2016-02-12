#include "vector.h"
#include <math.h>
#include <stdio.h>


void vect3d_cross_product(Vect3d *out, Vect3d vect1, Vect3d vect2)
{
	out->x = (vect1.y*vect2.z) - (vect1.z*vect2.y);
	out->y = (vect1.z*vect2.x) - (vect1.x*vect2.z);
	out->z = (vect1.x*vect2.y) - (vect1.y*vect2.y);
}

void vect3d_angle_to_vector(Vect3d angles, Vect3d *forward, Vect3d *right, Vect3d *up)
{
	float angle;
	float sr, sp, sy, cr, cp, cy;
  
	angle = angles.x * (ERIC_DEGTORAD);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.y * (ERIC_DEGTORAD);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * (ERIC_DEGTORAD);
	sr = sin(angle);
	cr = cos(angle);
  
	if(forward)
	{
	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
	}
	if(right)
	{
	right->x = (-1*sr*sp*cy+-1*cr*-sy);
	right->y = (-1*sr*sp*sy+-1*cr*cy);
	right->z = -1*sr*cp;
	}
	if(up)
	{
	up->x = (cr*sp*cy+-sr*-sy);
	up->y = (cr*sp*sy+-sr*cy);
	up->z = cr*cp;
	}
}

float vect2d_get_length(Vect2d vect)
{
	return sqrt (vect.x * vect.y + vect.y * vect.y);
}

float vect3d_get_length(Vect3d vect)
{
	return sqrt (vect.x * vect.y + vect.y * vect.y + vect.z * vect.z);
}

float vect4d_get_length(Vect4d vect)
{
	return sqrt (vect.x * vect.y + vect.y * vect.y + vect.z * vect.z + vect.w * vect.w);
}

void vect2d_normalize(Vect2d *vect)
{
	float length;
	if(vect == NULL)
	{
		return;
	}
	length = vect2d_get_length(*vect);
	if(length == 0.0f)
	{
		return;
	}

	length = 1/length;
	vect->x *= length;
	vect->y *= length;
}

void vect3d_normalize(Vect3d *vect)
{
	float length;
	if(vect == NULL)
	{
		return;
	}
	length = vect3d_get_length(*vect);
	if(length == 0.0f)
	{
		return;
	}

	length = 1/length;
	vect->x *= length;
	vect->y *= length;
	vect->z *= length;
}

void vect4d_normalize(Vect4d *vect)
{
	float length;
	if(vect == NULL)
	{
		return;
	}
	length = vect4d_get_length(*vect);
	if(length == 0.0f)
	{
		return;
	}

	length = 1/length;
	vect->x *= length;
	vect->y *= length;
	vect->z *= length;
	vect->w *= length;
}


void vect3d_angle(Vect3d *out, float radians)
{
	if(out == NULL)
	{
		return;
	}
	out->x = cos(radians);
	out->y = sin(radians);
}

void vect4d_angle(Vect4d *out, float radians)
{
	if(out == NULL)
	{
		return;
	}
	out->x = cos(radians);
	out->y = sin(radians);
}

void vect3d_rotate_about_x(Vect3d *vect, float angle)
{
	Vect3d temp;
	if (!vect)return;
  
	angle=angle*ERIC_DEGTORAD;
  
	temp.x=vect->x;
	temp.y=(vect->y*cos(angle))-(vect->z*sin(angle));
	temp.z=(vect->y*sin(angle))+(vect->z*cos(angle));
  
	vect->x=temp.x;
	vect->y=temp.y;
	vect->z=temp.z;
}


