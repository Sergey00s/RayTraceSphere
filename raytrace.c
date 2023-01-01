#include "minirt.h"



t_vec3 ray_color2(t_ray ray, int depth)
{
    t_vec3 col;
    t_hit hit;
    t_ray shadow_r;
    
    if (check_intersections(ray, &hit))
    {
        shadow_r = cr_ray(hit.p, unit_vector(sub(hit.p, gen.light.center)));
        if (!shadow_ray(shadow_r, hit.obj))
        {
            return (point_light2(&hit, gen.light, hit.color));
        }
        else
            return vec3(0.0, 0.0, 0.0);
        
    }
    return (vec3(0.15, 0.15, 0.15));
}



int check_intersections(t_ray ray, t_hit *hit)
{
    t_vec3 col;
    double tmin;
    t_scene *temp;
    temp = gen.scene;
    tmin = -1;
    while (temp)
    {
        int i = 0;        
        while (i < temp->object.mesh->size)
        {
            if (dot(temp->object.mesh->triangles[i].normal, sub(ray.origin, ray.direction)) < 0.0)
            {
                i++;
                continue;
            }
            if (call_back(ray, temp->object.mesh->triangles[i], &(hit->t), &hit->p))
            {
                
                if (tmin == -1 || (hit->t < tmin && hit->t > 0.0))
                {
                    tmin = hit->t;
                    hit->normal = temp->object.mesh->triangles[i].normal;
                    hit->obj = &temp->object.mesh;
                    hit->color = temp->object.color;
                }
            }
            i++;
        }
        temp = temp->next;
    }
    if (tmin != -1)
    {
        hit->p = ray_on_at(ray, tmin);
        return 1;
    }
    return 0;
}



int shadow_ray(t_ray ray, void *not)
{
    t_hit hit;
    t_scene *temp;
    temp = gen.scene;
    while (temp)
    {
        int i = 0;
        while (&temp->object.mesh != not && i < temp->object.mesh->size)
        {
            // if (dot(temp->object.mesh->triangles[i].normal, sub(ray.origin, ray.direction)) < 0.0)
            // {
            //     i++;
            //     continue;
            // }
            if (&temp->object.mesh->triangles[i] != not && call_back(ray, temp->object.mesh->triangles[i], &(hit.t), &hit.p))
            {
                if (hit.t > 0.0)
                {
                    return 1;
                }
                
            }
            i++;
        }
        temp = temp->next;
    }
    return 0;
}