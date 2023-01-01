#include "minirt.h"


t_vec3 centroid_3d(t_triangle tris) 
{

    t_vec3 vertex1; 
    t_vec3 vertex2; 
    t_vec3 vertex3;

    vertex1 = tris.a;
    vertex2 = tris.b;
    vertex3 = tris.c;
  // Find the midpoints of the sides of the triangle
  t_vec3 midpoint1;
  midpoint1.x = (vertex1.x + vertex2.x) / 2;
  midpoint1.y = (vertex1.y + vertex2.y) / 2;
  midpoint1.z = (vertex1.z + vertex2.z) / 2;
  
  t_vec3 midpoint2;
  midpoint2.x = (vertex2.x + vertex3.x) / 2;
  midpoint2.y = (vertex2.y + vertex3.y) / 2;
  midpoint2.z = (vertex2.z + vertex3.z) / 2;
  
  t_vec3 midpoint3;
  midpoint3.x = (vertex3.x + vertex1.x) / 2;
  midpoint3.y = (vertex3.y + vertex1.y) / 2;
  midpoint3.z = (vertex3.z + vertex1.z) / 2;
  
  // Find the point where the three medians intersect
  t_vec3 centroid;
  centroid.x = (midpoint1.x + midpoint2.x + midpoint3.x) / 3;
  centroid.y = (midpoint1.y + midpoint2.y + midpoint3.y) / 3;
  centroid.z = (midpoint1.z + midpoint2.z + midpoint3.z) / 3;
  
  return centroid;
}



double point_ray_distance(t_vec3 point, t_ray ray)
{
    t_vec3 projection = add(ray.origin, mpv(ray.direction, dot(sub(point, ray.origin), ray.direction)));

    double distance = sqrt(
  (projection.x - point.x) * (projection.x - point.x) +
  (projection.y - point.y) * (projection.y - point.y) +
  (projection.z - point.z) * (projection.z - point.z)
    );
return distance;
}