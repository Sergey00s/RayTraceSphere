#include "minirt.h"


double max(double x, double y)
{
    if (x > y)
        return x;
    return y;
}

t_vec3 ray_on_at(t_ray ray, double t)
{
    return (add(ray.origin, mpv(ray.direction, t)));
}