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
               // u = (i + random_double()) / (image.width -1);
                u = ((double)(i)) / (image.width -1);
               //  v = (j + random_double()) / (image.height -1);
                v = ((double)(j)) / (image.height -1);        
                ray_s = cr_ray(cam.origin, direction(cam, u, v));
                
                curcol = add(ray_color2(ray_s, 5), curcol);
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


t_vec3 center_of_triangle(t_triangle tri)
{
    t_vec3 a;

    a = add(tri.a, tri.b);
    a = add(a, tri.c);
    a = dvd(a, 3);
    return a;
}



int main(int argc, char const *argv[])
{

    t_cam mycam;
    t_img myimg;
    t_scene *myscene;
    myimg.a_ratio = 16.0/9.0;
    myimg.width = 1080;
    myimg.height = (int)myimg.width / myimg.a_ratio;
    mycam = cam(2.0, 2.0, myimg.a_ratio, vec3(0, 0, 2));
    gen.light.center = vec3(1, 0, -1);
    gen.light.brightness = 25;
    gen.light.color = vec3(1, 0, 0);
    char *filename;
    char *temp;
    //t_mesh *a;
    //subdivide(a);
    //printf("aut\n");
    add_scene("sph", vec3(0, -0.8, -2), vec3(1, 0, 0), cyldata(0.2, 0.6, 0));


    //add_scene("pln", vec3(0, -0.8, -2), vec3(1, 0, 0), cyldata(0.2, 0.6, 0));
    //add_scene("cyl", vec3(0, -0.8, -2), vec3(1, 0, 0), cyldata(0.2, 0.6, 0));
    

  // add_scene("cyl", vec3(0, 1, -4), vec3(1, 0, 0), cyldata(0.2, 0.3, 0));
    FILE *fd;
    
    fd = openppm("frames/new.ppm", myimg.width, myimg.height);
    render(mycam, myimg, fd);
    fclose(fd);
    return 0;
}
