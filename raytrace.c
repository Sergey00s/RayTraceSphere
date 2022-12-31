#include "minirt.h"


t_vec3 ray_color2(t_ray ray, int depth)
{
    t_vec3 col;
    t_hit hit;
    t_hit shadow;
    t_ray shadow_ray;
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
            if (call_back(ray, temp->object.mesh->triangles[i], &(hit.t), &hit.p))
            {
                if (tmin == -1 || hit.t < tmin)
                {
                    tmin = hit.t;
                       //hit2.p = ray_on_at(ray, hit.t);
                    col = temp->object.mesh->triangles[i].normal;
                    //col = vec3(1, 1, 1); //point_light2(&hit2, , vec3(1,0,0));
                }
            }
            i++;
        }
        temp = temp->next;
    }
    if (tmin != -1)
        return col;
    return (vec3(0.15, 0.15, 0.15));
}