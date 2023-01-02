#include "minirt.h"

t_scene *scene_obj(t_object object)
{
    t_scene *rtn;
    size_t size;

    size = sizeof(t_scene);
    rtn = malloc(size + 4);
    rtn->next = NULL;
    rtn->prev = NULL;
    rtn->object = object;
    return rtn;
}

void scene_add_back(t_scene **self, t_scene *newscn)
{
    t_scene *temp;

    if (*self == NULL)
    {
        *self = newscn;
        return;
    }
    temp = *self;
    while (temp->next)
        temp = temp->next;
    temp->next = newscn;
}

void calculate_normals(t_mesh *mesh)
{
    int i;

    i = 0;

    while (i < mesh->size)
    {
        t_vec3 ab = sub((mesh->triangles[i].a), mesh->triangles[i].b);
        t_vec3 ac = sub((mesh->triangles[i].a), mesh->triangles[i].c);
        t_vec3 norm = unit_vector(cross(ac, ab));
        (mesh->triangles[i]).normal = norm;
        i++;
    }


}

t_cyl cyldata(double radius, double height, double size, t_vec3 dir)
{
    t_cyl cyldata;
    
    cyldata.dir = dir;
    cyldata.r = radius;
    cyldata.h = height;
    cyldata.size = size;
    return cyldata;
}



void add_scene(char *name, t_vec3 center, t_vec3 color, t_cyl data)
{
    scene_add_back(&(gen.scene), scene_obj(object(name, center, color, data)));
}