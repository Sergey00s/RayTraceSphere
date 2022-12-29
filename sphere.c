#include "minirt.h"


void smooth_normals(t_mesh *mesh)
{
    t_vec3 a;
    t_vec3 b;
    t_vec3 c;
    t_vec3 d;
    int i;

    i = 0;
    while (i < mesh->size)
    {
        if (mesh->size - 1 == i)
        {
            b = mesh->triangles[i - 1].normal;
            c = mesh->triangles[i].normal;
            d = add(b, c);
            d = dvd(d, 2);
            mesh->triangles[i].normal = d;
        }
        else if (i == 0)
        {
            b = mesh->triangles[i].normal;
            c = mesh->triangles[i + 1].normal;
            d = add(b, c);
            d = dvd(d, 2);
            mesh->triangles[i].normal = d;
        }
        else
        {
            a = mesh->triangles[i - 1].normal;
            b = mesh->triangles[i].normal;
            c = mesh->triangles[i + 1].normal;
            d = add(a, b);
            d = add(c, d);
            d = dvd(d, 3);
            mesh->triangles[i].normal = unit_vector(d);
        }
        i++;
    }    
}


