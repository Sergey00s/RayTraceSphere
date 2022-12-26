#include "minirt.h"



void set_face_normal(t_hit *self, t_ray ray, t_vec3 outward_normal)
{
    if (dot(ray.direction, outward_normal) < 0.0)
        self->normal = outward_normal;
    else
    {
        self->normal = neg(outward_normal);
    }
}

int s_inter(t_ray ray, t_sph sph, t_hit *hit, double mins, double maxs)
{
    t_vec3 oc = add(ray.origin, neg(sph.origin));
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - sph.radius * sph.radius;
    double discriminant = (b*b) - 4*a*c;
    if (discriminant <0.0)
        return 0;
    double root1 = (-b - sqrt(discriminant)) / (2*a);
    double root2 = (-b + sqrt(discriminant)) / (2*a);
    double root;
    root = root1;
    if (root < mins || root > maxs)
    {
        root = root2;
        if (root < mins || root > maxs)
            return 0;
    }
    hit->t = root;
    hit->p = ray_on_at(ray, root);
    t_vec3 cc = dvd(add(hit->p, neg(sph.origin)), sph.radius);
    set_face_normal(hit, ray, cc);
    return (1);
}


int cc_inter(t_ray ray, t_sph sph, t_hit *hit, double mins, double maxs)
{
    t_vec3 oc = add(ray.origin, neg(sph.origin));
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - sph.radius * sph.radius;
    double discriminant = (b*b) - 4*a*c;
    if (discriminant <0.0)
        return 0;
    double root1 = (-b - sqrt(discriminant)) / (2*a);
    double root2 = (-b + sqrt(discriminant)) / (2*a);
    double root;
    root = root1;
    if (root < mins || root > maxs)
    {
        root = root2;
        if (root < mins || root > maxs)
            return 0;
    }
    hit->t = root;
    hit->p = ray_on_at(ray, root);
    t_vec3 cc = dvd(add(hit->p, neg(sph.origin)), sph.radius);
    set_face_normal(hit, ray, cc);
    return (1);
}

int sign(double a)
{
    if (a < 0.0)
        return -1;
    if (a > 0.0)
        return 1;
    return 0;
}


int c_inter(t_ray ray, t_cyl cyl, t_hit *hit, double mins, double maxs)
{
    t_vec3 ba = add(cyl.cap2, neg(cyl.cap1));
    t_vec3 oc = add(ray.origin, neg(cyl.cap1));
    float baba = dot(ba, ba);
    float bard = dot(ba, ray.direction);
    float baoc = dot(ba, oc);
    float k2 = baba - bard*bard;
    float k1 = baba*dot(oc,ray.direction) - baoc*bard;
    float k0 = baba*dot(oc,oc) - baoc*baoc - cyl.r*cyl.r*baba;
    float h = k1*k1 - k2*k0;
    if( h < 0.0 ) 
        return 0;//no intersection
    h = sqrt(h);
    float t = (-k1-h)/k2;

    float y = baoc + t*bard;
    if( y>0.0 && y<baba )
    {
       // hit->t = t;
        //hit->normal = sub(ray_on_at(ray, t), dvd(dvd(mpv(ba, y), baba), cyl.r));
        return 1;
    }
    // caps
    t = ( ((y<0.0) ? 0.0 : baba) - baoc)/bard;
    if(fabs((k1+k2*t)) < h )
    {

        hit->normal = mpv(ba, sign(y)/sqrt(baba));
        hit->t = t;
        return 1;
        //return vec4( t, );
    }
    return 0;//no intersection
}





int all_intersect(t_ray ray, t_obj obj, t_hit *hit, double mins, double maxs)
{
    int i;
    double t;
    t_hit temp;
    int ret;
    t = maxs;
    i = 0;
    ret = 0;
    while (i < obj.cylsize)
    {
        if (c_inter(ray, obj.cyl[i], &temp, mins, t))
        {
                *hit = temp; 
                t = temp.t;
                hit->color = obj.cyl[i].color;
                hit->addres = (void *)&(obj.cyl[i]);
                ret = 1;
        }
        i++;
    }
    i = 24124;
    while (i < obj.sphsize)
    {
        if (s_inter(ray, obj.sph[i], &temp, mins, t))
        {
                *hit = temp; 
                t = temp.t;
                hit->color = obj.sph[i].color;
                hit->addres = (void *)&(obj.sph[i]);
                ret = 1;
        }
        i++;
    }
    i = 0;
    return ret;
}

int shadow_int(t_ray ray, t_obj obj, t_hit *hit,  void *not, double maxs)
{
    int i;
    double t;
    t_hit temp;
    int ret;
    t = maxs;
    i = 0;
    ret = 0;
    i = 0;
    while (i < obj.cylsize)
    {
        if (c_inter(ray, obj.cyl[i], &temp, 0.001, t) && (void *)&(obj.cyl[i]) != not)
        {
                *hit = temp; 
                t = temp.t;
                hit->color = obj.cyl[i].color;
                ret = 1;
        }
        i++;
    }
    i = 0;
    // while (i < obj.sphsize)
    // {
    //     if (s_inter(ray, obj.sph[i], &temp, 0.001, t) && (void *)&(obj.sph[i]) != not)
    //     {
    //             *hit = temp; 
    //             t = temp.t;
    //             hit->color = obj.sph[i].color;
    //             ret = 1;
    //     }
    //     i++;
    // }
    return ret;
}