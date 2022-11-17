#include "humanoid.hpp"
#include "globals.hpp"
#include <unordered_map>

std::unordered_map<string,csX75::HNode*> umap;

glm::vec4 positions[8] = {
  glm::vec4(0.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, 0.25, 0.25, 1.0),
  glm::vec4(2.0, 0.25, 0.25, 1.0),
  glm::vec4(2.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, -0.25, -0.25, 1.0),
  glm::vec4(0.0, 0.25, -0.25, 1.0),
  glm::vec4(2.0, 0.25, -0.25, 1.0),
  glm::vec4(2.0, -0.25, -0.25, 1.0)
};

glm::vec4 positions_1[8] = {
  glm::vec4(0.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, 0.25, 0.25, 1.0),
  glm::vec4(-2.0, 0.25, 0.25, 1.0),
  glm::vec4(-2.0, -0.25, 0.25, 1.0),
  glm::vec4(0.0, -0.25, -0.25, 1.0),
  glm::vec4(0.0, 0.25, -0.25, 1.0),
  glm::vec4(-2.0, 0.25, -0.25, 1.0),
  glm::vec4(-2.0, -0.25, -0.25, 1.0)
};

glm::vec4 positions_2[8] = {
  glm::vec4(-1.0, 0, 0.25, 1.0),
  glm::vec4(-1.0, 2, 0.25, 1.0),
  glm::vec4(1.0, 2, 0.25, 1.0),
  glm::vec4(1.0, 0, 0.25, 1.0),
    glm::vec4(-1.0, 0, -0.25, 1.0),
    glm::vec4(-1.0, 2, -0.25, 1.0),
    glm::vec4(1.0, 2, -0.25, 1.0),
    glm::vec4(1.0, 0, -0.25, 1.0),
};

glm::vec4 positions_3[8] = {
  glm::vec4(-2.0, 0, 0.25, 1.0),
  glm::vec4(-2.0, 0.5, 0.25, 1.0),
  glm::vec4(2.0, 0.5, 0.25, 1.0),
  glm::vec4(2.0, 0, 0.25, 1.0),
    glm::vec4(-2.0, 0, -0.25, 1.0),
    glm::vec4(-2.0, 0.5, -0.25, 1.0),
    glm::vec4(2.0, 0.5, -0.25, 1.0),
    glm::vec4(2.0, 0, -0.25, 1.0),
};

glm::vec4 positions_4[8] = {
  glm::vec4(0.75, 0, 0.25, 1.0),
  glm::vec4(0.75, 1, 0.25, 1.0),
  glm::vec4(1.25, 1, 0.25, 1.0),
  glm::vec4(1.25, 0, 0.25, 1.0),
    glm::vec4(0.75, 0, -0.25, 1.0),
    glm::vec4(0.75, 1, -0.25, 1.0),
    glm::vec4(1.25, 1, -0.25, 1.0),
    glm::vec4(1.25, 0, -0.25, 1.0),
};

//RGBA colors
glm::vec4 colors[8] = {
  glm::vec4(0.9, 0.74, 0.67, 1.0),
  glm::vec4(0.9, 0.74, 0.67, 1.0),
  glm::vec4(0.9, 0.74, 0.67, 1.0),
  glm::vec4(0.9, 0.74, 0.67, 1.0),
  glm::vec4(0.9, 0.74, 0.67, 1.0),
  glm::vec4(0.9, 0.74, 0.67, 1.0),
  glm::vec4(0.9, 0.74, 0.67, 1.0),
  glm::vec4(0.9, 0.74, 0.67, 1.0)
};

glm::vec4 colors_1[8] = {
  glm::vec4(0.08, 0.37, 0.74, 1.0),
    glm::vec4(0.08, 0.37, 0.74, 1.0),
    glm::vec4(0.08, 0.37, 0.74, 1.0),
    glm::vec4(0.08, 0.37, 0.74, 1.0),
    glm::vec4(0.08, 0.37, 0.74, 1.0),
    glm::vec4(0.08, 0.37, 0.74, 1.0),
    glm::vec4(0.08, 0.37, 0.74, 1.0),
    glm::vec4(0.08, 0.37, 0.74, 1.0),
};

glm::vec4 colors_2[8] = {
  glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
};


int tri_idx=0;
const int num_vertices = 36;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_positions_1[num_vertices];
glm::vec4 v_positions_2[num_vertices];
glm::vec4 v_positions_3[num_vertices];
glm::vec4 v_positions_4[num_vertices];
glm::vec4 v_colors[num_vertices];
const int num_vertices_face = 100000;
glm::vec4 v_positions_5[num_vertices_face];
glm::vec4 v_colors_1[num_vertices_face];
double PI=3.14159265;
glm::vec4 skin_color(0.9, 0.74, 0.67, 1.0);

void sphere(double radius, int Lats, int Longs)
{
  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;

  for (lats = 0.0; lats <= PI; lats+=sectors)
  {
      for(longs = 0.0; longs <= 2.0*PI; longs+=slices)
      {
          float x = radius * sin(lats) * cos(longs);
          float y = radius * sin(lats) * sin(longs);
          float z = radius * cos(lats);
          glm::vec4 pt(x, y, z, 1.0);

          v_colors_1[tri_idx] = skin_color; v_positions_5[tri_idx] = pt;
          tri_idx++;
          
          if(lats+sectors>PI)
            l=PI;
          else
            l=lats+sectors;
          x = radius * sin(l) * cos(longs);
          y = radius * sin(l) * sin(longs);
          z = radius * cos(l);
          pt =glm::vec4(x, y, z, 1.0);
          v_colors_1[tri_idx] = skin_color; v_positions_5[tri_idx] = pt;
          tri_idx++;
      }
    }
}

void quad(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors_1[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors_1[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
  v_colors[tri_idx] = colors_1[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors_1[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors_1[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors_1[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
 }

void quad_1(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors_1[a]; v_positions_1[tri_idx] = positions_1[a]; tri_idx++;
  v_colors[tri_idx] = colors_1[b]; v_positions_1[tri_idx] = positions_1[b]; tri_idx++;
  v_colors[tri_idx] = colors_1[c]; v_positions_1[tri_idx] = positions_1[c]; tri_idx++;
  v_colors[tri_idx] = colors_1[a]; v_positions_1[tri_idx] = positions_1[a]; tri_idx++;
  v_colors[tri_idx] = colors_1[c]; v_positions_1[tri_idx] = positions_1[c]; tri_idx++;
  v_colors[tri_idx] = colors_1[d]; v_positions_1[tri_idx] = positions_1[d]; tri_idx++;
 }

void quad_2(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors[a]; v_positions_2[tri_idx] = positions_2[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions_2[tri_idx] = positions_2[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions_2[tri_idx] = positions_2[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_positions_2[tri_idx] = positions_2[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions_2[tri_idx] = positions_2[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions_2[tri_idx] = positions_2[d]; tri_idx++;
 }

void quad_3(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors_2[a]; v_positions_3[tri_idx] = positions_3[a]; tri_idx++;
  v_colors[tri_idx] = colors_2[b]; v_positions_3[tri_idx] = positions_3[b]; tri_idx++;
  v_colors[tri_idx] = colors_2[c]; v_positions_3[tri_idx] = positions_3[c]; tri_idx++;
  v_colors[tri_idx] = colors_2[a]; v_positions_3[tri_idx] = positions_3[a]; tri_idx++;
  v_colors[tri_idx] = colors_2[c]; v_positions_3[tri_idx] = positions_3[c]; tri_idx++;
  v_colors[tri_idx] = colors_2[d]; v_positions_3[tri_idx] = positions_3[d]; tri_idx++;
 }

void quad_4(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors[a]; v_positions_4[tri_idx] = positions_4[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions_4[tri_idx] = positions_4[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions_4[tri_idx] = positions_4[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_positions_4[tri_idx] = positions_4[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions_4[tri_idx] = positions_4[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions_4[tri_idx] = positions_4[d]; tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(void)
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

void colorcube_1(void)
{
    quad_1( 1, 0, 3, 2 );
    quad_1( 2, 3, 7, 6 );
    quad_1( 3, 0, 4, 7 );
    quad_1( 6, 5, 1, 2 );
    quad_1( 4, 5, 6, 7 );
    quad_1( 5, 4, 0, 1 );
}

void colorcube_2(void)
{
    quad_2( 1, 0, 3, 2 );
    quad_2( 2, 3, 7, 6 );
    quad_2( 3, 0, 4, 7 );
    quad_2( 6, 5, 1, 2 );
    quad_2( 4, 5, 6, 7 );
    quad_2( 5, 4, 0, 1 );
}

void colorcube_3(void)
{
    quad_3( 1, 0, 3, 2 );
    quad_3( 2, 3, 7, 6 );
    quad_3( 3, 0, 4, 7 );
    quad_3( 6, 5, 1, 2 );
    quad_3( 4, 5, 6, 7 );
    quad_3( 5, 4, 0, 1 );
}

void colorcube_4(void)
{
    quad_4( 1, 0, 3, 2 );
    quad_4( 2, 3, 7, 6 );
    quad_4( 3, 0, 4, 7 );
    quad_4( 6, 5, 1, 2 );
    quad_4( 4, 5, 6, 7 );
    quad_4( 5, 4, 0, 1 );
}

csX75::HNode* make_humanoid()
{
    colorcube();
    tri_idx=0;
    hip = new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    hip->change_parameters(-1.0,0.0,0.0,0.0,0.0,0.0);
    uLegR = new csX75::HNode(hip,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    uLegR->change_parameters(2.0,0.0,0.0,90.0,290.0,0.0);
    lLegR = new csX75::HNode(uLegR,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    lLegR->dof_y = false;
    lLegR->dof_z = false;
    colorcube_1();
    tri_idx=0;
    lLegR->change_parameters(2.0,0.0,0.0,0.0,340.0,0.0);
    uLegL = new csX75::HNode(hip,num_vertices,v_positions_1,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    uLegL->change_parameters(0.0,0.0,0.0,90.0,70.0,0.0);
    lLegL = new csX75::HNode(uLegL,num_vertices,v_positions_1,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    lLegL->dof_y = false;
    lLegL->dof_z = false;
    lLegL->change_parameters(-2.0,0.0,0.0,0.0,20.0,0.0);
    colorcube_2();
    tri_idx=0;
    colorcube_3();
    tri_idx=0;
    torso = new csX75::HNode(hip,num_vertices,v_positions_2,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    torso->change_parameters(1.0,0.0,0.0,0.0,0.0,0.0);
    shoulder = new csX75::HNode(torso,num_vertices,v_positions_3,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    shoulder->change_parameters(0.0,2.0,0.0,0.0,0.0,0.0);
    uArmR = new csX75::HNode(shoulder,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    uArmR->change_parameters(2,0.25,0.0,90.0,300.0,0.0);
    lArmR = new csX75::HNode(uArmR,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    lArmR->dof_x = false;
    lArmR->dof_y = false;
    lArmR->change_parameters(2.0,0.0,0.0,0.0,320.0,0.0);
    uArmL = new csX75::HNode(shoulder,num_vertices,v_positions_1,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    uArmL->change_parameters(-2.0,0.25,0.0,90.0,60.0,0.0);
    lArmL = new csX75::HNode(uArmL,num_vertices,v_positions_1,v_colors,sizeof(v_positions),sizeof(v_colors),false);
    lArmL->dof_x = false;
    lArmL->dof_y = false;
    lArmL->change_parameters(-2.0,0.0,0.0,0.0,40.0,0.0);
    colorcube_4();
    tri_idx=0;
    neck = new csX75::HNode(shoulder,num_vertices,v_positions_4,v_colors,sizeof(v_positions_4),sizeof(v_colors),false);
    neck->change_parameters(-1.0,0.5,0.0,0.0,0.0,0.0);
    neck->dof_x = false;
    neck->dof_y = false;
    neck->dof_z = false;
    sphere(1, 100, 100);
    head = new csX75::HNode(neck,num_vertices_face,v_positions_5,v_colors_1,sizeof(v_positions_5),sizeof(v_colors_1),true);
    head->change_parameters(1.0,2.0,0.0,0.0,0.0,0.0);
    return hip;
}
