#include "minirt.h"

void rotateX(double* x, double* y, double* z, double angle) 
{
  float rad = angle * PI / 180.0;
  float cos_a = cos(rad);
  float sin_a = sin(rad);
  float newY = *y * cos_a - *z * sin_a;
  float newZ = *y * sin_a + *z * cos_a;
  *y = newY;
  *z = newZ;
}


void rotateY(double* x, double* y, double* z, double angle) 
{
  float rad = angle * PI / 180.0;
  float cos_a = cos(rad);
  float sin_a = sin(rad);
  float newX = *x * cos_a + *z * sin_a;
  float newZ = -*x * sin_a + *z * cos_a;
  *x = newX;
  *z = newZ;
}


void rotateZ(double* x, double* y, double* z, float angle) 
{
  float rad = angle * PI / 180.0;
  float cos_a = cos(rad);
  float sin_a = sin(rad);
  float newX = *x * cos_a - *y * sin_a;
  float newY = *x * sin_a + *y * cos_a;
  *x = newX;
  *y = newY;
}

void rotate(t_mesh *mesh, float angle, int axis)
{
  int i;

  i = 0;
  while (i < mesh->size)
  {
    if (axis == 0)
    {
      rotateX(&mesh->triangles[i].a.x, &mesh->triangles[i].a.y, &mesh->triangles[i].a.z, angle);
      rotateX(&mesh->triangles[i].b.x, &mesh->triangles[i].b.y, &mesh->triangles[i].b.z, angle);
      rotateX(&mesh->triangles[i].c.x, &mesh->triangles[i].c.y, &mesh->triangles[i].c.z, angle);

    }
    else if (axis == 1)
    {
      rotateZ(&mesh->triangles[i].a.x, &mesh->triangles[i].a.y, &mesh->triangles[i].a.z, angle);
       rotateZ(&mesh->triangles[i].b.x, &mesh->triangles[i].b.y, &mesh->triangles[i].b.z, angle);
       rotateZ(&mesh->triangles[i].c.x, &mesh->triangles[i].c.y, &mesh->triangles[i].c.z, angle);
    }
    else if (axis == 2)
    {
       rotateY(&mesh->triangles[i].a.x, &mesh->triangles[i].a.y, &mesh->triangles[i].a.z, angle);
       rotateY(&mesh->triangles[i].b.x, &mesh->triangles[i].b.y, &mesh->triangles[i].b.z, angle);
       rotateY(&mesh->triangles[i].c.x, &mesh->triangles[i].c.y, &mesh->triangles[i].c.z, angle);
    }
    i++;
  }
  
}
