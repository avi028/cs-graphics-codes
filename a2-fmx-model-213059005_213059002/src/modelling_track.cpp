#include "modelling_track.hpp"
#include "cylinder.hpp"
#include "frustum.hpp"
#include "humanoid.hpp"
#include "modelling_bike.hpp"
using namespace std;

GLuint terrain_vbo,terrain_vao,terrain_ibo;
vector<glm::vec4> terrain_v_positions;
vector<glm::vec4> terrain_v_color;
vector<GLuint> terrain_indices;
csX75::HNode* ground_node;
csX75::HNode* patch1_node;
csX75::HNode* patch2_node;
csX75::HNode* patch3_node;
csX75::HNode* patch4_node;
csX75::HNode* turn1_node;
csX75::HNode* turn2_node;
csX75::HNode* turn3_node;
csX75::HNode* turn4_node;
csX75::HNode* prism1_leftside_node;
csX75::HNode* prism1_rightside_node;
csX75::HNode* prism2_leftside_node;
csX75::HNode* prism2_flatsurface_node;
csX75::HNode* prism2_rightside_node;

int tesselation = 500;
float dx;
float dz;
//-----------------------------------------------------------------
void clear()
{
    terrain_v_positions.clear();
    terrain_v_color.clear();
    terrain_indices.clear();
}
int find_index(int v)
{
    return v/dx;
}

void init_terrain_vertices(int length,int width, glm::vec4 color)
{
    clear();
    float x = 0.0;
    float z = 0.0;
    int terrain_length = length;
    int terrain_width = width;
    //float y = 1.0;
    dx = (float)terrain_length/(float)tesselation;
    dz = (float)terrain_width/(float)tesselation;
    for(int i=0;i<tesselation;i++)
    {
        z+=dz;
        x=0.0;
        for(int j=0;j<tesselation;j++)
        {
            terrain_v_positions.push_back(glm::vec4(x,0.0,z,1.0));
            terrain_v_color.push_back(color);
            x+=dx;
        }
    }
    
    for(int i=0;i<tesselation-1;i++)
    {
        for(int j=0;j<tesselation;j++)
        {
            terrain_indices.push_back(i*tesselation+j);
            terrain_indices.push_back((i+1)*tesselation+j);
        }
    }
}

void inti_for_turn(int width, glm::vec4 color)
{
    clear();
    float theta = 0.0;

    int terrain_width = width/2;
    dx = (float)terrain_width/(float)tesselation;
    dz = (float)terrain_width/(float)tesselation;
    float dtheta = (float)1.6/(float)tesselation;
    
    for(int i=0;i<tesselation;i++)
    {
            terrain_v_positions.push_back(glm::vec4(2*terrain_width*cos(theta),0.0,2*terrain_width*sin(theta),1.0));
            terrain_v_color.push_back(color);
            theta+=dtheta;
    }
    theta = 0.0;
    for(int i=0;i<tesselation;i++)
    {
            terrain_v_positions.push_back(glm::vec4(terrain_width*cos(theta),0.0,terrain_width*sin(theta),1.0));
            terrain_v_color.push_back(color);
            theta+=dtheta;
    }
    for(int i=0;i<tesselation;i++)
    {
            terrain_indices.push_back(i);
            terrain_indices.push_back(tesselation+i);
    }
}

void init_leftside_prism(int height,int width,int road_width,glm::vec4 color)
{
    clear();
    float x = 0.0;
    float z = 0.0;
    int terrain_width = road_width;
    dx = (float)(width/2)/(float)tesselation;
    dz = (float)terrain_width/(float)tesselation;
    float m = (float)height/(float)(width/2);
    float c = (float)height - (float)(m*(float)(width/2));
    
    for(int i=0;i<tesselation;i++)
    {
        x=0.0;
        for(int j=0;j<tesselation;j++)
        {
            if(i>0 && i<tesselation-5)
            {
                terrain_v_positions.push_back(glm::vec4(x,m*x+c,z,1.0));
            }
            else
            {
                terrain_v_positions.push_back(glm::vec4(x,0.0,z,1.0));
            }
            terrain_v_color.push_back(color);
            x+=dx;
        }
        z+=dz;
    }
    for(int i=0;i<tesselation-1;i++)
    {
        for(int j=0;j<tesselation;j++)
        {
            terrain_indices.push_back(i*tesselation+j);
            terrain_indices.push_back((i+1)*tesselation+j);
        }
    }
}

void init_rightside_prism(int height,int width,int road_width,glm::vec4 color)
{
    clear();
    float x = (float)(width/2);;
    float z = 0.0;
    int terrain_width = road_width;
    dx = (float)(width/2)/(float)tesselation;
    dz = (float)terrain_width/(float)tesselation;
    float m = (-1.0*(float)height)/((float)(width)-height);
    float c = (float)height - (float)(m*(float)(width/2));
    
    for(int i=0;i<tesselation;i++)
    {
        x=(float)(width/2);
        for(int j=0;j<tesselation;j++)
        {
            if(i>0 && i<tesselation-5)
            {
                terrain_v_positions.push_back(glm::vec4(x,m*x+c,z,1.0));
            }
            else
            {
                terrain_v_positions.push_back(glm::vec4(x,0.0,z,1.0));
            }
            terrain_v_color.push_back(color);
            //cout<<terrain_v_positions[tesselation*i+j].x<<","<<terrain_v_positions[tesselation*i+j].y<<","<<terrain_v_positions[tesselation*i+j].z<<endl;
            x+=dx;
        }
        z+=dz;
    }
    for(int i=0;i<tesselation-1;i++)
    {
        for(int j=0;j<tesselation;j++)
        {
            terrain_indices.push_back(i*tesselation+j);
            terrain_indices.push_back((i+1)*tesselation+j);
        }
    }
}

void init_flate_surface_at_height(int height,int width,int road_width,glm::vec4 color)
{
    clear();
    float x = (float)(width/2);
    float z = 0.0;
    int terrain_width = road_width;
    dx = (float)(width/2)/(float)tesselation;
    dz = (float)terrain_width/(float)tesselation;
    
    for(int i=0;i<tesselation;i++)
    {
        x=(float)(width/2);
        for(int j=0;j<tesselation;j++)
        {
            if(i>0 && i<tesselation-5)
            {
                terrain_v_positions.push_back(glm::vec4(x,height,z,1.0));
            }
            else
            {
                terrain_v_positions.push_back(glm::vec4(x,0.0,z,1.0));
            }
            terrain_v_color.push_back(color);
            //cout<<terrain_v_positions[tesselation*i+j].x<<","<<terrain_v_positions[tesselation*i+j].y<<","<<terrain_v_positions[tesselation*i+j].z<<endl;
            x+=dx;
        }
        z+=dz;
    }
    for(int i=0;i<tesselation-1;i++)
    {
        for(int j=0;j<tesselation;j++)
        {
            terrain_indices.push_back(i*tesselation+j);
            terrain_indices.push_back((i+1)*tesselation+j);
        }
    }
}

csX75::HNode* make_track()
{
    Cylinder *  center = new Cylinder(4,3.0,1.0,glm::vec4(0.44,0.33,0.24,1.00));
    csX75::HNode * ground_Center1 =  new csX75::HNode(NULL,center->indices,center->vertices,center->verticesColor);
    ground_Center1->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);

    center = new Cylinder(4,3.0,1.0,glm::vec4(0.44,0.33,0.24,1.00));
    csX75::HNode * ground_Center2 =  new csX75::HNode(ground_Center1,center->indices,center->vertices,center->verticesColor);
    ground_Center2->change_parameters(0.0,0.0,0.0,0.0,90.0,0.0);
    init_terrain_vertices(200,200,glm::vec4(0.40,0.74,0.33,1.00));
    ground_node = new csX75::HNode(ground_Center1, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    ground_node->change_parameters(-100.0,0.0,-50.0,0.0,0.0,0.0);
    
    init_terrain_vertices(140,20,glm::vec4(0.44,0.33,0.24,1.00));
    patch1_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    patch1_node->change_parameters(30.0,0.1,10.0,0.0,0.0,0.0);
    
    init_terrain_vertices(140,20,glm::vec4(0.44,0.33,0.24,1.00));
    patch2_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    patch2_node->change_parameters(30.0,0.1,80.0,0.0,0.0,0.0);
    
    init_terrain_vertices(40,20,glm::vec4(0.44,0.33,0.24,1.00));
    patch3_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    patch3_node->change_parameters(10.0,0.1,70.0,0.0,90.0,0.0);
    
    init_terrain_vertices(40,20,glm::vec4(0.44,0.33,0.24,1.00));
    patch4_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    patch4_node->change_parameters(179.0,0.1,70.0,0.0,90.0,0.0);
    
    inti_for_turn(20,glm::vec4(0.44,0.33,0.24,1.00));
    turn1_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    turn1_node->change_parameters(30.0,0.1,30.0,0.0,180.0,0.0);
    
    inti_for_turn(20,glm::vec4(0.44,0.33,0.24,1.00));
    turn2_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    turn2_node->change_parameters(30.0,0.1,70.0,0.0,-90.0,0.0);
    
    inti_for_turn(20,glm::vec4(0.44,0.33,0.24,1.00));
    turn3_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    turn3_node->change_parameters(169.0,0.1,30.0,0.0,90.0,0.0);
    
    inti_for_turn(20,glm::vec4(0.44,0.33,0.24,1.00));
    turn4_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    turn4_node->change_parameters(169.0,0.1,70.0,0.0,-360.0,0.0);
    
    init_leftside_prism(10,20,20,glm::vec4(0.44,0.33,0.74,1.00));
    prism1_leftside_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    prism1_leftside_node->change_parameters(50.0,0.0,80.0,0.0,0.0,0.0);
    
    init_rightside_prism(10,20,20,glm::vec4(0.44,0.33,0.74,1.00));
    prism1_rightside_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    prism1_rightside_node->change_parameters(50.0,0.0,80.0,0.0,0.0,0.0);
    
    init_leftside_prism(10,20,20,glm::vec4(0.44,0.33,0.74,1.00));
    prism2_leftside_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    prism2_leftside_node->change_parameters(90.0,0.0,80.0,0.0,0.0,0.0);
    
    init_flate_surface_at_height(10,20,20,glm::vec4(0.44,0.33,0.74,1.00));
    prism2_flatsurface_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    prism2_flatsurface_node->change_parameters(90.0,0.0,80.0,0.0,0.0,0.0);
    
    init_rightside_prism(10,20,20,glm::vec4(0.44,0.33,0.74,1.00));
    prism2_rightside_node = new csX75::HNode(ground_node, (int)terrain_v_positions.size(), terrain_v_positions, terrain_v_color, terrain_indices, terrain_v_positions.size()*sizeof(glm::vec4), terrain_v_color.size()*sizeof(glm::vec4), true);
    prism2_rightside_node->change_parameters(100.0,0.0,80.0,0.0,0.0,0.0);

    Cylinder * c = new Cylinder(24,30.0,10.0,glm::vec4(0.44,0.33,0.74,1.00));
    c->setPartialSectorIndices(6);
    csX75::HNode * cylinderHalf =  new csX75::HNode(ground_node,c->indices,c->vertices,c->verticesColor);
    cylinderHalf->change_parameters(60.0,-23.0,15.0,0.0,0.0,45.0f);

    c = new Cylinder(4,10.0,10.0,glm::vec4(0.44,0.33,0.74,1.00));
    c->setPartialSectorIndices(1);
    cylinderHalf =  new csX75::HNode(ground_node,c->indices,c->vertices,c->verticesColor);
    cylinderHalf->change_parameters(15.0,0.0,45.0,0.0,90.0,90.0f);
    
    c = new Cylinder(24,30.0,10.0,glm::vec4(0.44,0.33,0.74,1.00));
    c->setPartialSectorIndices(3);
    cylinderHalf =  new csX75::HNode(ground_node,c->indices,c->vertices,c->verticesColor);
    cylinderHalf->change_parameters(130.0,-23.0,15.0,0.0,0.0,90.0f);

    
    csX75::HNode * bike = drawBike();
    ground_node->add_child(bike);    
    bike->change_parameters(185.0,5.0,45.0,-90.0,0.0,90.0f);

    csX75::HNode * rider = make_humanoid();
    bike->add_child(rider) ;   
    rider->change_parameters(0.0,-1.0,5.0,90.0,90.0,0.0f);
    return ground_Center1;

}
