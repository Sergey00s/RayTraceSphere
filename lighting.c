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



// vec4 cylIntersect( in vec3 ro, in vec3 rd, in vec3 pa, in vec3 pb, float ra )
// {
//     vec3 ba = pb-pa;
//     vec3 oc = ro - pa;
//     float baba = dot(ba,ba);
//     float bard = dot(ba,rd);
//     float baoc = dot(ba,oc);
//     float k2 = baba            - bard*bard;
//     float k1 = baba*dot(oc,rd) - baoc*bard;
//     float k0 = baba*dot(oc,oc) - baoc*baoc - ra*ra*baba;
//     float h = k1*k1 - k2*k0;
//     if( h<0.0 ) return vec4(-1.0);//no intersection
//     h = sqrt(h);
//     float t = (-k1-h)/k2;
//     // body
//     float y = baoc + t*bard;
//     if( y>0.0 && y<baba ) return vec4( t, (oc+t*rd - ba*y/baba)/ra );
//     // caps
//     t = ( ((y<0.0) ? 0.0 : baba) - baoc)/bard;
//     if( abs(k1+k2*t)<h )
//     {
//         return vec4( t, ba*sign(y)/sqrt(baba) );
//     }
//     return vec4(-1.0);//no intersection
// }