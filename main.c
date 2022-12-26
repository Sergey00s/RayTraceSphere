#include "minirt.h"


t_gen gen;

t_cam cam(double h, double fl, double aspect_ratio, t_vec3 origin)
{
    t_cam rtn;

    rtn.v_h = h;
    rtn.v_w = aspect_ratio * rtn.v_h;
    rtn.fl = 1.0;
    rtn.origin = origin;
    rtn.horizontal = vec3(rtn.v_w,0, 0);
    rtn.vertical = vec3(0, rtn.v_h, 0);
    rtn.lower_left = add(neg(dvd(rtn.vertical, 2)), neg(vec3(0, 0, fl)));
    rtn.lower_left= add(neg(dvd(rtn.horizontal, 2)), rtn.lower_left);
    rtn.lower_left = add(origin, rtn.lower_left);
    return rtn;
}

t_vec3 direction(t_cam cam, double u, double v)
{
    t_vec3 rtn;
    
    rtn = sub(mpv(cam.vertical, v), cam.origin);
    rtn = add(mpv(cam.horizontal, u), rtn);
    rtn = add(cam.lower_left, rtn);
    return rtn;
}
void render(t_cam cam, t_img image, FILE *stream)
{
    double u;
    double v;
    t_ray ray_s;
    t_vec3 curcol;


    
  for (int j = image.height - 1; j >= 0; --j) {
        for (int i = 0; i < image.width; ++i) {
            curcol = vec3(0, 0, 0);
            for (size_t samp = 0; samp < 1; samp++)
            {
                u = (i + random_double()) / (image.width -1);
                v = (j + random_double()) / (image.height -1);        
                ray_s = cr_ray(cam.origin, direction(cam, u, v));
                curcol = add(ray_color(ray_s, 5), curcol);
            }
            write_color(stream, curcol, 1);
        }
    }
}

t_ray cr_ray(t_vec3 origin, t_vec3 direction)
{
    t_ray rtn;

    rtn.origin = origin;
    rtn.direction = direction;
    return  rtn;
}

double normal_value(double val, double min, double max)
{
    double value_normalized;

    value_normalized = (val - min) / (max - min);
    return value_normalized;
}


double Convert(double radian)
{
    double pi = 3.14159;
    double rtn; 

    rtn = radian * (180 / pi);
    if (rtn > 360)
    {
        while (rtn > 360.0)
        {
            rtn = rtn - 360;
        }
    }
    return(radian * (180 / pi));
}




t_vec3 ray_color(t_ray ray, int depth)
{
    int a;

    t_hit hit;
    double dist;
    double val;
    hit.front_face = 0;
    t_hit shadow;
    t_ray shadow_ray;
    t_vec3 taget;

  
  int i = 0;
    while (i < gen.obje->mesh->size)
    {
        if (call_back(ray, gen.obje->mesh->triangles[i], &hit.t, &hit.p))
        {
            t_vec3 ab = sub((gen.obje->mesh->triangles[i].a), gen.obje->mesh->triangles[i].b);
            t_vec3 ac = sub((gen.obje->mesh->triangles[i].a), gen.obje->mesh->triangles[i].c);
            t_vec3 norm = cross(ac, ab);
            if (dot(ray.direction, norm) > 0.0)
            {
                norm = (norm);
            }
            norm = unit_vector(neg(norm));
            printf("%f %f %f\n", norm.x, norm.y, norm.z);
            return norm;
        }
        i++;
    }
    return vec3(0,0,0);
    if (depth <= 0)
    {
        return vec3(0, 0, 0);
    }
    a = all_intersect(ray, *(gen.obj), &hit, 0.01, __DBL_MAX__);
    if (a)
    {   
        t_vec3 color;
        t_hit hit_shadow;
        shadow_ray = cr_ray((hit.p) , gen.light.center);
        if (shadow_int(shadow_ray, *(gen.obj), &hit_shadow, hit.addres, __DBL_MAX__))
        {
            //return(vec3(0.1, 0.1, 0.1));
            taget = add(add(hit_shadow.p, hit_shadow.normal), random_in_unit_sphere()); 
            return mpv(mp(ray_color(cr_ray(hit_shadow.p, add(taget, neg(hit_shadow.p))), depth - 1), hit.color), 0.04);
        }
        color = point_light2(&hit, gen.light, hit.color);
        taget = add(add(hit.p, hit.normal), random_in_unit_sphere()); 
        return mp(mpv(color, 0.5), ray_color(cr_ray(hit.p, add(taget, neg(hit.p))), depth - 1));
    }
    return (vec3(0.15, 0.15, 0.15));
}



t_vec3 circ(int frame)
{
    t_vec3 result;

    float angle = frame * 0.3;
    float x = 2 * cos(angle);
    float y = 2 * sin(angle);
    
    return vec3(x, 1, y);
}

int main(int argc, char const *argv[])
{

    t_cam mycam;
    t_img myimg;


    myimg.a_ratio = 16.0/9.0;
    myimg.width = 1080;
    myimg.height = (int)myimg.width / myimg.a_ratio;
    mycam = cam(2.0, 2.0, myimg.a_ratio, vec3(0, 0, 5));
    //gen.obj = objs();
       // FILE *fd = openppm("image.ppm", myimg.width, myimg.height);
    gen.light.center = vec3(1, 0, -1);
    gen.light.brightness = 25;
    gen.light.color = vec3(1, 0, 0);
    char *filename;
    char *temp;
    t_cyl a;
    a.h = 1;
    a.r = 1;
    t_object obje = object("cyl", vec3(0, 0, 0), vec3(0, 0, 1), &a);
    gen.obje = &obje;
    FILE *fd;
    for (size_t frame = 0; frame < 1; frame++)
    {   
        temp = ft_itoa(frame);
        filename = ft_strjoin("frames/image", temp);
        free(temp);
        temp = ft_strjoin(filename, ".ppm");
        free(filename);
        fd = openppm(temp, myimg.width, myimg.height);
        free(temp);
        gen.light.center = circ(frame);
        render(mycam, myimg, fd);
        fclose(fd);
        ft_putnbr_fd(frame, 1);
        ft_putchar_fd('\n', 1);
    }
    return 0;
}
