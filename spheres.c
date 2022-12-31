#include "minirt.h"

void drawSphere(double r, int lats, int longs, t_mesh *self)
 {
    
        float pi = 3.141592;
        float di = 0.02;
        float dj = 0.04;
        float db = di * 2 * pi;
        float da = dj * pi;
    
    
        for (float i = 0; i < 1.0; i += di) //horizonal
            for (float j = 0; j < 1.0; j += dj) //vertical
            {
                float b = i * 2 * pi;      //0     to  2pi
                float a = (j - 0.5) * pi;  //-pi/2 to pi/2

                //glBegin(GL_QUADS);
                //P1
                    //glTexCoord2f(i, j);
                    t_vec3 p1 = vec3(
                        r * cos(a) * cos(b),
                        r * cos(a) * sin(b),
                        r * sin(a));
                //P2
                    
                    t_vec3 p2 = vec3(
                        r * cos(a) * cos(b + db),
                        r * cos(a) * sin(b + db),
                        r * sin(a));
                //P3
                   
                    t_vec3 p3 = vec3(
                        r * cos(a + da) * cos(b + db),
                        r * cos(a + da) * sin(b + db),
                        r * sin(a + da));
                //P4
                    
                   t_vec3 p4 = vec3(
                        r * cos(a + da) * cos(b),
                        r * cos(a + da) * sin(b),
                        r * sin(a + da));
                    t_triangle left = triangle(p1, p4, p3);
                    t_triangle right = triangle(p3, p2, p1);
                    mesh_append(self, left);
                    mesh_append(self, right);
            }
    }
    