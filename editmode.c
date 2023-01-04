#include "minirt.h"

// int intersect_triangle3(double orig[3], double dir[3],double vert0[3], double vert1[3], double vert2[3],
// 			double *t, double *u, double *v)
// {
//    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
//    double det,inv_det;

//    /* find vectors for two edges sharing vert0 */
//    SUB(edge1, vert1, vert0);
//    SUB(edge2, vert2, vert0);
   
//    /* begin calculating determinant - also used to calculate U parameter */
//    CROSS(pvec, dir, edge2);
//    /* if determinant is near zero, ray lies in plane of triangle */
//    det = DOT(edge1, pvec);
//    /* calculate distance from vert0 to ray origin */
//    SUB(tvec, orig, vert0);
//    inv_det = 1.0 / det;
   
//    CROSS(qvec, tvec, edge1);
      
//    if (det > EPSILON)
//    {
//       *u = DOT(tvec, pvec);
//       if (*u < 0.0 || *u > det)
// 	 return 0;
           
//       /* calculate V parameter and test bounds */
//       *v = DOT(dir, qvec);
//       if (*v < 0.0 || *u + *v > det)
// 	 return 0;
      
//    }
//    else if(det < -EPSILON)
//    {
//       /* calculate U parameter and test bounds */
//       *u = DOT(tvec, pvec);
//       if (*u > 0.0 || *u < det)
// 	 return 0;
      
//       /* calculate V parameter and test bounds */
//       *v = DOT(dir, qvec) ;
//       if (*v > 0.0 || *u + *v < det)
// 	 return 0;
//    }
//    else return 0;  /* ray is parallell to the plane of the triangle */

//    *t = DOT(edge2, qvec) * inv_det;
//    (*u) *= inv_det;
//    (*v) *= inv_det;
//    return 1;
// }


int call_back(t_ray ray, t_triangle tris, double *value, t_vec3 *pos)
{
    int result;
    double u;
    double v;
    t_hit hit;

    result = intersect_triangle(ray, tris, &hit);
    // result = intersect_triangle3((double[]){ray.origin.x,ray.origin.y,ray.origin.z},
    // (double[]){ray.direction.x,ray.direction.y,ray.direction.z},  
    //         (double[]){tris.a.x, tris.a.y, tris.a.z},
    //         (double[]){tris.b.x, tris.b.y, tris.b.z},
    //         (double[]){tris.c.x, tris.c.y, tris.c.z},
	// 		value, &u, &v);
    //*pos = calculate_pos(tris, u, v);
    //*pos = ray_on_at(ray, *value);
    *value = hit.t;
    return result;
}