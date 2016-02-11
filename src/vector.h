#ifndef __VECTOR_H__
#define __VECTOR_H__

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
#define vect2d_negate(neg,vect)      (neg.x=(-vect.x), neg.y=-(vect.y))

/**
 * @brief	A macro that takes a vect3d and negates it.
 * @param	neg 	The resulting negative vect3d.
 * @param	vect	The vect3d to be negated.
 */
#define vect3d_negate(neg,vect)      (neg.x=(-vect.x), neg.y=(-vect.y), neg.z=(-vect.z))

/**
 * @brief	A macro that takes a vect4d and negates it.
 * @param	neg 	The resulting negative vect4d.
 * @param	vect	The vect4d to be negated.
 */
#define vect4d_negate(neg,vect)      (neg.x=(-vect.x), neg.y=(-vect.y), neg.z=(-vect.z), neg.w=(-vect.w))


#endif
