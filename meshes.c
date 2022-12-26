#include "minirt.h"

t_triangle triangle(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
    t_triangle t;
    t.a = v1;
    t.b = v2;
    t.c = v3;
    return t;
}

t_mesh *mesh(void)
{
    t_mesh *mesh;

    mesh = malloc(sizeof(t_mesh) * 1);
    mesh->size = 0;
    mesh->triangles = NULL;
    return mesh;
}

void mesh_append(t_mesh *self, t_triangle triangle)
{
    t_triangle *temp;
    int i;
 
    if (!self)
        return;
    temp = self->triangles;
    self->triangles = malloc(sizeof(t_triangle) * (self->size + 1));
    i = 0;
    while (i < self->size)
    {
        self->triangles[i] = temp[i];
        i++;
    }
    self->triangles[i] = triangle;
    self->size++;
    free(temp);
}


t_mesh *make_cylinder(t_vec3 *arr, t_cyl *data, double h, t_vec3 *arr2, int sectors)
{
    t_mesh *mmes;
    int i;

    mmes = mesh();
    i = 0;
    while (i + 1 < (sectors))
    {
        mesh_append(mmes, triangle(vec3(0, 0, 0), arr[i], arr[i + 1]));
        i++;
    }
    i = 0;
    while (i + 1 < (sectors))
    {
        mesh_append(mmes, triangle(vec3(0, data->h,0), arr2[i], arr2[i + 1]));
        i++;
    }
    i = 0;
    while (i < (sectors))
    {
        mesh_append(mmes, triangle(arr2[i], arr2[i + 1], arr[i]));
        i++;
    }
    i = 0;
    while (i < (sectors))
    {
        mesh_append(mmes, triangle(arr[i], arr[i + 1], arr2[i + 1]));
        i++;
    }
    return mmes;
}


void move_mesh(t_mesh *mesh, t_vec3 to)
{
    int i;

    i = 0;
    while (i < mesh->size)
    {
        (mesh->triangles[i]).a = add((mesh->triangles[i]).a, to);
       (mesh->triangles[i]).b = add((mesh->triangles[i]).b, to); 
       (mesh->triangles[i]).c = add((mesh->triangles[i]).c, to); 
        i++;
    }
}

void cylinder(t_mesh **self, t_cyl *data)
{
    
    t_vec3 *arr;
    t_vec3 *arr2;
    t_vec3 *temp;
    double degree;
    int sectorCount = 40;
    float sectorStep = 2 * PI / sectorCount;
    double x;
    double y;
    double z;
    int h;
    degree = 0;
    h = 0;
    int i;
    arr = malloc(sizeof(t_vec3) * (sectorCount + 1));
    arr2 = malloc(sizeof(t_vec3) * (sectorCount + 1));
    i = -1;
    h = 0;
    t_vec3 center = vec3(0.0, 0.0, 0);

    while (++i < sectorCount)
    {
        degree = i * sectorStep;
        x = data->r * cos(degree) + center.x;
        y = data->r * sin(degree) + center.y;
        z = 0;
        arr[h] = vec3(x, z, y);
        h++;
    }
    h = 0;
    i = -1;
    while (++i < sectorCount)
    {
        degree = i * sectorStep;
        x = data->r * cos(degree) + center.x;
        y = data->r * sin(degree) + center.y;
        z = data->h;
        arr2[h] = vec3(x, z, y);
        h++;
    }
    *self = make_cylinder(arr, data, h, arr2, sectorCount);
    move_mesh(*self, add(neg(vec3(0, 0, 0)), vec3(0, -2, -2)));
}

t_object object(char *name, t_vec3 center, t_vec3 color, void *data)
{
    t_object obj;

    obj.center = center;
    obj.color = color;
    obj.name = name;
    if (ft_strncmp("sph", name, ft_strlen(name)) == 0)
    {
        //sph   
    }
    else if (ft_strncmp("cyl", name, ft_strlen(name)) == 0)
    {
        cylinder(&(obj.mesh), data);

    }
    else if (ft_strncmp("pln", name, ft_strlen(name)) == 0)
    {
        // pln
    }
    return obj;
}

