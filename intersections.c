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



int all_intersect(t_ray ray, t_obj obj, t_hit *hit, double mins, double maxs)
{
    int i;
    double t;
    t_hit temp;
    int ret;
    t = maxs;
    i = 0;
    ret = 0;
    while (i < obj.sphsize)
    {
        if (s_inter(ray, obj.sph[i], &temp, mins, t))
        {
                *hit = temp; 
                t = temp.t;
                hit->color = obj.sph[i].color;
                hit->sph = &(obj.sph[i]);
                ret = 1;
        }
        i++;
    }
    return ret;
}

int shadow_int(t_ray ray, t_obj obj, t_hit *hit, t_sph *not, double maxs)
{
    int i;
    double t;
    t_hit temp;
    int ret;
    t = maxs;
    i = 0;
    ret = 0;
    while (i < obj.sphsize)
    {
        if (s_inter(ray, obj.sph[i], &temp, 0.001, t) && &(obj.sph[i]) != not)
        {
                *hit = temp; 
                t = temp.t;
                hit->color = obj.sph[i].color;
                ret = 1;
        }
        i++;
    }
    return ret;
}