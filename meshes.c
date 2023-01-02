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

    mesh = malloc(sizeof(t_mesh));
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
    self->triangles = malloc(sizeof(t_triangle) * (self->size + 2));
    i = 0;
    while (i < self->size)
    {
        self->triangles[i] = temp[i];
        i++;
    }
    free(temp);
    self->triangles[i] = triangle;
    self->size++;
}

t_mesh *make_cylinder(t_vec3 *bot, t_cyl *data, double h, t_vec3 *top, int sectors)
{
    t_mesh *mmes;
    t_vec3 a;
    t_vec3 b;
    t_vec3 c;
    int i;

    mmes = mesh();
    i = 0;
    while (i < (sectors))
    {
        if (i < (sectors - 1))
            mesh_append(mmes, triangle(vec3(0, 0, 0), bot[i + 1], bot[i]));
        else
            mesh_append(mmes, triangle(vec3(0, 0, 0), bot[0], bot[i]));        
        i++;
    }
    i = 0;
    while (i < (sectors))
    {
        if (i < (sectors - 1))
            mesh_append(mmes, triangle(vec3(0, data->h,0), top[i], top[i + 1]));        
        else
            mesh_append(mmes, triangle(vec3(0, data->h,0), top[i], top[0])); 
        i++;
    }
    i = 0;
    while (i < (sectors))
    {
        if (i < (sectors - 1))
        {
            a = top[i + 1];
            c = bot[i + 1];
        }
        else
        {
            a =  top[0];
            c =  bot[0];
        }
        b = top[i];
        mesh_append(mmes, triangle(a, b, c));
        if (i < (sectors - 1))
        {
            c = bot[i + 1];
        }
        else 
            c = bot[0];        
        a = top[i];
        b = bot[i];
        mesh_append(mmes, triangle(a, b, c));
        i++;
    }
    free(bot);
    free(top);
    return mmes;
}


void move_mesh(t_mesh *mesh, t_vec3 to)
{
    int i;

    i = 0;
    while (i <= mesh->size)
    {
        (mesh->triangles[i]).a = add((mesh->triangles[i]).a, to);
       (mesh->triangles[i]).b = add((mesh->triangles[i]).b, to); 
       (mesh->triangles[i]).c = add((mesh->triangles[i]).c, to); 
        i++;
    }
}

void cylinder(t_mesh **self, t_cyl *data, t_vec3 center)
{
    
    t_vec3 *arr;
    t_vec3 *arr2;
    t_vec3 *temp;
    double degree;
    int sectorCount = 15;
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
    i = 0;
    h = 0;
    while (++i <= sectorCount)
    {
        degree = i * (sectorStep);
        x = data->r * cos(degree);
        y = data->r * sin(degree);
        z = 0;
        arr[h] = vec3(x, z, y);
        h++;
    }
    h = 0;
    i = 0;
    while (++i <= sectorCount)
    {
        degree = i * sectorStep;
        x = data->r * cos(degree);
        y = data->r * sin(degree);
        z = data->h;
        arr2[h] = vec3(x, z, y);
        h++;
    }
    *self = make_cylinder(arr, data, h, arr2, sectorCount);
    rotate_by_directions(*self, data->dir);
    move_mesh(*self, add(neg(vec3(0, 0, 0)), center));
    calculate_normals(*self);
}



void plane(t_mesh **self, t_cyl *data, t_vec3 center)
{
    t_vec3 a;
    t_vec3 b;
    t_vec3 c;
    t_vec3 d;

    *self = mesh();
    a = vec3(-1 * data->size, 0, -1 * data->size);
    b = vec3(1* data->size, 0, -1*data->size);
    c = vec3(-1 * data->size, 0, 1*data->size);
    d = vec3(1 * data->size, 0, 1 * data->size);
    mesh_append(*self, triangle(a, b, d));
    mesh_append(*self, triangle(d, c, a));
    rotate_by_directions(*self, data->dir);
    move_mesh(*self, center);
    calculate_normals(*self);
}


t_object object(char *name, t_vec3 center, t_vec3 color, t_cyl data)
{
    t_object obj;

    obj.center = center;
    obj.color = color;
    obj.name = name;
    if (ft_strncmp("sph", name, ft_strlen(name)) == 0)
    {
        obj.mesh = mesh();
        drawSphere(data.r, 0, 0, obj.mesh);
        //rotate(obj.mesh, 90, 0);
        rotate_by_directions(obj.mesh, data.dir);
        move_mesh(obj.mesh, center);
        calculate_normals(obj.mesh);
    }
    else if (ft_strncmp("cyl", name, ft_strlen(name)) == 0)
    {
        cylinder(&(obj.mesh), &data, center);
    }
    else if (ft_strncmp("pln", name, ft_strlen(name)) == 0)
    {
        plane(&(obj.mesh), &data, center);
    }
    return obj;
}

