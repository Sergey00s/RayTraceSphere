#include "minirt.h"


double to_radians(double degree)
{
    double rad;
    
    rad = (degree * PI) / 180;
    return rad;
}


t_gen gen;

t_cam cam(double aspect_ratio, t_vec3 origin, t_vec3 dir, t_vec3 vup, float fow)
{
    t_cam rtn;



    double theta = to_radians(fow);
    double h = tan(theta / 2);

    rtn.v_h = 2.0 * h;
    rtn.v_w = aspect_ratio * rtn.v_h;


    t_vec3 w  = unit_vector(sub(origin, dir));
    t_vec3 u = unit_vector(cross(vup, w));
    t_vec3 v = cross(w, u);
    rtn.fl = 1.0;
    rtn.origin = origin;
    rtn.horizontal = mpv(u, rtn.v_w);
    rtn.vertical = mpv(v, rtn.v_h);
    // origin - horizontal/2 - vertical/2 - w

    rtn.lower_left = add(neg(dvd(rtn.vertical, 2)), neg(w));
    rtn.lower_left = add(neg(dvd(rtn.horizontal, 2)), rtn.lower_left);
    rtn.lower_left = add(origin, rtn.lower_left);
    // rtn.lower_left = add(neg(dvd(rtn.vertical, 2)), neg(w));
    // rtn.lower_left= add(neg(dvd(rtn.horizontal, 2)), rtn.lower_left);
    // rtn.lower_left = add(origin, rtn.lower_left);
    return rtn;
}

t_vec3 direction(t_cam cam, double u, double v)
{
    t_vec3 rtn;
    
 //   lower_left_corner + s*horizontal + t*vertical - origin
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
    t_vec3 optimum;
    t_vec3 temp;
  for (int j = image.height - 1; j >= 0; --j) {
        for (int i = 0; i < image.width; ++i) {
            //curcol = vec3(0, 0, 0);
            for (size_t samp = 0; samp < 1; samp++)
            {
                if (i % 3 == 0 || 1)
                {
                    u = ((double)(i)) / (image.width -1);
                   //u = (i + random_double()) / (image.width -1);
                       v = ((double)(j)) / (image.height -1);
                   // v = (j + random_double()) / (image.height -1);
                    ray_s = cr_ray(cam.origin, direction(cam, u, v));
                    //printf("%f %f %f\n", ray_s.direction.x, ray_s.direction.y, ray_s.direction.z);
                    optimum = ray_color2(ray_s, 5);
                    temp = optimum;
                }
                else
                    optimum = temp;
                curcol = optimum;//add(optimum, curcol);
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
    myimg.width = 480;
    myimg.height = (int)myimg.width / myimg.a_ratio;
    mycam = cam(myimg.a_ratio, vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0), 90);
    gen.ambient_ratio = 0.3;
    gen.ambient_color = vec3(0.2, 0.2, 0.3);
    gen.ambient_salt = mpv(gen.ambient_color, 0.5 * gen.ambient_ratio);
    gen.light.center = vec3(0.5, 0, 0.1);
    gen.light.brightness = 1;
    gen.light.color = vec3(1, 1, 1);
    char *filename;
    char *temp;

    add_scene("pln", vec3(0, 0, 3), vec3(1, 1, 1), cyldata(0.5, 0.4, 2, vec3(0, 0, -1)));
    add_scene("pln", vec3(0, 1, 2), vec3(1, 1, 1), cyldata(0.5, 0.4, 1, vec3(0, -1, 0)));
    add_scene("pln", vec3(1, -0, 2), vec3(1, 1, 1), cyldata(0.5, 0.4, 1, vec3(1, 0, 0)));
    add_scene("pln", vec3(-1, -0, 2), vec3(1, 1, 1), cyldata(0.5, 0.4, 1, vec3(-1, 0, 0)));
    add_scene("pln", vec3(0, -1, 2), vec3(1, 1, 1), cyldata(0.5, 0.4, 1, vec3(0, 1, 0)));
    //add_scene("sph", vec3(-0.4, 0.2, -2), vec3(0, 0, 1), cyldata(0.2, 0.4, 1, vec3(-1, 0, 0)));
    //add_scene("sph", vec3(0, 0.2, -2), vec3(1, 0, 0), cyldata(0.2, 0.4, 1, vec3(-1, 0, 0)));
    //add_scene("sph", vec3(0.4, 0.2, -2), vec3(0, 1, 0), cyldata(0.2, 0.4, 1, vec3(-1, 0, 0)));
    add_scene("cyl", vec3(0, -1, 2), vec3(1, 0, 0.5), cyldata(0.4, 0.7, 1, vec3(0, 1, 0)));
    
   // add_scene("sph", vec3(0, 1.6, -2), vec3(0, 0, 1), cyldata(0.05, 0.4, 1, vec3(-1, 0, 0)));
    



    //add_scene("pln", vec3(-0.5, -1, -2), vec3(0, 1, 0.5), cyldata(0.5, 0.4, 3, vec3(-1, 0, 0)));
    //add_scene("cyl", vec3(-1, 0, -2), vec3(1, 0, 0), cyldata(0.5, 1, 0, vec3(0, -1, 0)));
    //add_scene("sph", vec3(-1, 0, -2), vec3(1, 0, 0), cyldata(0.5, 0.6, 0, vec3(0, 1, 0)));
    //add_scene("sph", vec3(-1, 1, -3), vec3(1, 1, 0), cyldata(0.5, 0.6, 0, vec3(0, 1, 0)));
    //add_scene("pln", vec3(0, -1, -3), vec3(0.8, 0, 0.3), cyldata(0.7, 0.4, 3, vec3(0, 1, 0)));
    FILE *fd;
    fd = openppm("frames/new.ppm", myimg.width, myimg.height);
    clock_t start, end;
    double elapsed;
    start = clock();
    render(mycam, myimg, fd);
    end = clock();  
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // calculate elapsed time
    printf("Time elapsed: %.2f seconds\n", elapsed); 
    fclose(fd);
    return 0;
}
