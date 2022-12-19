#include "minirt.h"



double point_light(t_hit *h, t_vec3 lp, double brightness)
{
    double rtn;
    double dist;
    t_vec3 ld;
    
    ld = add((lp), neg(h->p));
    ld = dvd(ld, length(sub(lp, h->p)));
    rtn = max(dot(h->normal, ld), 0);
    //dist = distance(h->p, lp);
    
    return (rtn * brightness);

}



t_vec3 point_light2(t_hit *h, t_point light, t_vec3 color)
{
    double rtn;
    double dist;
    t_vec3 ld;
    
    ld = add((light.center), neg(h->p));
    ld = dvd(ld, length(sub(light.center, h->p)));
    rtn = max(dot(h->normal, ld), 0);
    rtn = rtn * light.brightness;
    dist = length_squared(sub(light.center, h->p));
    ld = dvd(mpv(color, rtn), dist);
   
    return (ld);

}
