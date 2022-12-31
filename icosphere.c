#include "minirt.h"


#define X 0.525731112119133606
#define Z 0.850650808352039932

t_vec3 vdata[12] = {    
  {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
  {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
  {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};

int tindices[20][3] = { 
  {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
  {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
  {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
  {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} 
};

typedef struct {
  t_vec3 *vertices;
  int num_vertices;
  int (*indices)[3];
  int num_indices;
} mes;

mes icosphere = { vdata, 12, tindices, 20 };

void subdivide(t_mesh *mymesh) {
    mes *m;

    m = &icosphere;
  // Create a new array to hold the subdivided vertices
  t_vec3 new_vertices[300];
  int num_new_vertices = 0;
  
  // Create a new array to hold the subdivided indices
  int new_indices[200][3];
  int num_new_indices = 0;
  
  // Iterate over the triangles of the mesh
  for (int i = 0; i < m->num_indices; i++) {
    // Get the indices of the triangle vertices
    int i1 = m->indices[i][0];
    int i2 = m->indices[i][1];
    int i3 = m->indices[i][2];
    
    // Get the vertices of the triangle
    t_vec3 v1 = m->vertices[i1];
    t_vec3 v2 = m->vertices[i2];
    t_vec3 v3 = m->vertices[i3];
    
    // Calcul
    // Calculate the midpoints of the triangle edges
    t_vec3 v12 = add(v1, v2); v12 = unit_vector(v12);
    t_vec3 v23 = add(v2, v3); v23 = unit_vector(v23);
    t_vec3 v31 = add(v3, v1); v31 = unit_vector(v31);
    
    // Add the midpoint vertices to the new vertex array
    new_vertices[num_new_vertices++] = v12;
    new_vertices[num_new_vertices++] = v23;
    new_vertices[num_new_vertices++] = v31;
    
    // Add the new triangles to the new index array
    //new_indices[num_new_indices++] = (int[3]){i1, num_new_vertices - 3, num_new_vertices - 2};
    //new_indices[num_new_indices++] = (int[3]){num_new_vertices - 2, i2, num_new_vertices - 1};
    //new_indices[num_new_indices++] = (int[3]){num_new_vertices - 1, i3, num_new_vertices - 3};
    //new_indices[num_new_indices++] = (int[3]){num_new_vertices - 3, num_new_vertices - 1, num_new_vertices - 2};
    t_triangle a = triangle(m->vertices[i1], m->vertices[num_new_vertices - 3], m->vertices[num_new_vertices - 2]);
    mesh_append(mymesh, a);
    a = triangle(m->vertices[num_new_vertices - 2], m->vertices[i2], m->vertices[num_new_vertices - 1]);
    mesh_append(mymesh, a);
    a = triangle(m->vertices[num_new_vertices - 1], m->vertices[i3], m->vertices[num_new_vertices - 3]);
    mesh_append(mymesh, a);
    a = triangle(m->vertices[num_new_vertices - 3], m->vertices[num_new_vertices - 1], m->vertices[num_new_vertices - 2]);
    mesh_append(mymesh, a);
  }
  
  // Replace the old vertex and index arrays with the new ones
//   free(m->vertices);
//   m->vertices = new_vertices;
//   m->num_vertices = num_new_vertices;
  
//   free(m->indices);
//   m->indices = new_indices;
//   m->num_indices = num_new_indices;
}

