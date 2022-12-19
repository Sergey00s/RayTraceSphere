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

typedef struct s_obj
{
    t_sph *sph;
    int sphsize;
}              t_obj;

typedef struct s_ray
{
    t_vec3 origin;
    t_vec3 direction;
}               t_ray;



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
    t_point light;
}               t_gen;

typedef struct s_hit
{
    double t;
    t_sph *sph;
    t_vec3 p;
    t_vec3 normal;
    t_vec3 color;
    int front_face;
}               t_hit;



extern t_gen gen;
t_obj *objs();
int shadow_int(t_ray ray, t_obj obj, t_hit *hit, t_sph *not, double maxs);
int all_intersect(t_ray ray, t_obj obj, t_hit *hit, double mins, double maxs);
void new_sph(t_obj *self,  t_vec3 pos, double r, t_vec3 color);
double max(double x, double y);
int s_inter(t_ray ray, t_sph sph, t_hit *hit, double mins, double maxs);
t_vec3 ray_color(t_ray ray);
t_ray cr_ray(t_vec3 origin, t_vec3 direction);
FILE *openppm(const char *name, int width, int height);
int write_ppm(int red, int green, int blue, FILE *fd);
t_vec3 ray_on_at(t_ray ray, double t);
void write_color(FILE *fd, t_vec3 px_color, int samples);
void set_face_normal(t_hit *self, t_ray ray, t_vec3 outward_normal);
double normal_value(double val, double min, double max);
double point_light(t_hit *h, t_vec3 lp, double maxdist);
t_vec3 point_light2(t_hit *h, t_point light, t_vec3 color);
#endif