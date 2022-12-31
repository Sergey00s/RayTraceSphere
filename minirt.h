#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <vec3d.h>
# include <libft.h>

# define PI 3.1415926
#define MYRAND_MAX 0xFFFF

# define IMAX 2147483647
#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 


typedef struct s_point
{
    t_vec3 center;
    double brightness;
    t_vec3 color;
}            t_point;

typedef struct  s_img
{
    int width;
    int height;
    double a_ratio;

}               t_img;


typedef struct s_sph
{
    t_vec3 origin;
    t_vec3 color;
    double radius;
}               t_sph;


typedef struct s_cyl
{
    t_vec3 origin;
    t_vec3 color;
    double r;
    double h;
    double size;

}               t_cyl;

typedef struct s_obj
{
    t_sph *sph;
    int sphsize;
    t_cyl *cyl;
    int cylsize;

}              t_obj;

typedef struct s_ray
{
    t_vec3 origin;
    t_vec3 direction;
}               t_ray;

typedef struct s_triangle
{
    t_vec3 a;
    t_vec3 b;
    t_vec3 c;

    t_vec3 normal;
}   t_triangle;

typedef struct s_mesh
{
    t_triangle *triangles;
    int size;
}               t_mesh;

typedef struct s_object
{
    char *name;
    t_mesh *mesh;
    t_vec3 center;
    t_vec3 direction;
    t_vec3 color;
}               t_object;

typedef struct s_scene
{
    t_object object;
    struct s_scene *next;
    struct s_scene *prev;

}               t_scene;

typedef struct s_cam
{
    double v_h;
    double v_w;
    double fl;
    t_vec3 origin;
    t_vec3 horizontal;
    t_vec3 vertical;
    t_vec3 lower_left;
    
}               t_cam;


typedef struct s_minirt
{
    t_cam cam;
    t_obj *obj;
    t_object *obje;
    t_point light;
    t_scene *scene;
}               t_gen;

typedef struct s_hit
{
    double t;
    void *addres;
    t_vec3 p;
    t_vec3 normal;
    t_vec3 color;
    int front_face;
}               t_hit;


extern t_gen gen;
void subdivide(t_mesh *mymesh);
void smooth_normals(t_mesh *mesh);
void add_scene(char *name, t_vec3 center, t_vec3 color, t_cyl data);
t_cyl cyldata(double radius, double height, double size);
t_vec3 ray_color2(t_ray ray, int depth);
t_scene *scene_obj(t_object object);
void scene_add_back(t_scene **self, t_scene *newscn);
void calculate_normals(t_mesh *mesh);
t_object object(char *name, t_vec3 center, t_vec3 color, t_cyl data);
int call_back(t_ray ray, t_triangle tris, double *value, t_vec3 *pos);
t_triangle triangle(t_vec3 v1, t_vec3 v2, t_vec3 v3);
t_mesh *mesh(void);
void mesh_append(t_mesh *self, t_triangle triangle);
void new_cyl(t_obj *self, t_vec3 pos, double r, double h, t_vec3 color);
int c_inter(t_ray ray, t_cyl cyl, t_hit *hit, double mins, double maxs);
int c_inter2(t_ray ray, t_cyl cyl, t_hit *hit, double mins, double maxs);
t_obj *objs();
int shadow_int(t_ray ray, t_obj obj, t_hit *hit, void *not, double maxs);
int all_intersect(t_ray ray, t_obj obj, t_hit *hit, double mins, double maxs);
void new_sph(t_obj *self,  t_vec3 pos, double r, t_vec3 color);
double max(double x, double y);
int s_inter(t_ray ray, t_sph sph, t_hit *hit, double mins, double maxs);
t_vec3 ray_color(t_ray ray, int depth);
t_ray cr_ray(t_vec3 origin, t_vec3 direction);
FILE *openppm(const char *name, int width, int height);
int write_ppm(int red, int green, int blue, FILE *fd);
t_vec3 ray_on_at(t_ray ray, double t);
void write_color(FILE *fd, t_vec3 px_color, int samples);
void set_face_normal(t_hit *self, t_ray ray, t_vec3 outward_normal);
double normal_value(double val, double min, double max);
double point_light(t_hit *h, t_vec3 lp, double maxdist);
t_vec3 point_light2(t_hit *h, t_point light, t_vec3 color);
unsigned rands();
double random_double();
t_vec3 random_f();
t_vec3 my_random(double min, double max);
t_vec3 random_in_unit_sphere();
double random_doubles(double min, double max);
void smooth_normals(t_mesh *mesh);
#endif