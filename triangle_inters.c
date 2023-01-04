#include "minirt.h"

int intersect_triangle(t_ray ray, t_triangle tri, t_hit *hit)
{
    t_vec3 edge1;
    t_vec3 edge2;
    t_vec3 tvec;
    t_vec3 pvec;
    t_vec3 qvec;
    double det;
    double inv_det;

    edge1 = sub(tri.b, tri.a);
    edge2 = sub(tri.c, tri.a);
    pvec = cross(ray.direction, edge2);
    det = dot(edge1, pvec);
    tvec = sub(ray.origin, tri.a);
    inv_det = 1.0 / det;
    qvec = cross(tvec, edge1);
    hit->u = dot(tvec, pvec);
    hit->v = dot(ray.direction, qvec);
    if (det > EPSILON)
    {
        if (hit->u < 0.0 || hit->u > det)
	        return 0;
        if (hit->v < 0.0 || (hit->u + hit->v) > det)
	        return 0;
    }
    else if (det < -EPSILON)
    {
        if (hit->u > 0.0 || hit->u < det)
	        return 0;
        if (hit->v > 0.0 || (hit->u + hit->v) < det)
	        return 0;
    }
    else
        return 0;
    hit->t = dot(edge2, qvec) * inv_det;
    hit->u *= inv_det;
    hit->v *= inv_det;
    return 1;
}