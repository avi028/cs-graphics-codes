#include "modelling_bike.hpp"
#include "cylinder.hpp"
#include "frustum.hpp"

extern csX75::HNode* tyref, *tyreb, *handlejoin, *bodyframe,* engine;

csX75::HNode * drawBike(){

  // Handle + front tyre
  float rodLen = 6.0;
  float rodAngle = -20.0;
  float tyre_Width = 0.8;
  float tyre_radius = 2.5;
  float h,w,l;


  // engine 
  w=1.0;
  h=2.5;
  l=3.0;

  csX75::HNode* node1;
  csX75::HNode* node2;
  csX75::HNode* node3;
  csX75::HNode* node4;
  csX75::HNode* node5;
  csX75::HNode* node6;
  csX75::HNode* node7;
  csX75::HNode* node8;

  csX75::HNode * handle[10];
  std::string tx("images/seat.bmp");

  Cylinder * c = new Cylinder(4,1.0,0.5,glm::vec4(1.0,1.0,0.0,1.0));
  handle[0] = new csX75::HNode(NULL,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[0]->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0f);
  handlejoin = handle[0];

  c = new Cylinder(24,0.20,2.0,glm::vec4(1.0,1.0,1.0,1.0));
  handle[1] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[1]->change_parameters(-1.30,0.0,0.40,0.0,120.0,0.0);

  handle[2] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[2]->change_parameters(1.30,0.0,0.40,0.0,60.0,0.0);

  c = new Cylinder(24,0.3,2.0,glm::vec4(0.0,1.0,1.0,1.0));
  handle[3] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[3]->change_parameters(-2.60,0.0,0.80,0.0,90.0,0.0);

  handle[4] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[4]->change_parameters(2.60,0.0,.80,0.0,90.0,0.0);

  c = new Cylinder(24,0.20,rodLen,glm::vec4(0.0,0.0,1.0,1.0));
  handle[5] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[5]->change_parameters(-0.50,-1.20,-1*(rodLen/2.0),rodAngle,0.0,0.0);
  
  handle[6] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[6]->change_parameters(0.50,-1.20,-1*(rodLen/2.0),rodAngle,0.0,0.0);

  c = new Cylinder(24,0.50,0.70,1.0,glm::vec4(1.0,1.0,1.0,1.0));
  handle[7] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[7]->change_parameters(0.0,-1.0,-2.0,90.0,0.0,0.0);

  c = new Cylinder(24,0.70,0.20,glm::vec4(1.0,1.0,0.0,1.0));
  handle[7] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[7]->change_parameters(0.0,-1.50,-2.0,90.0,0.0,0.0);

  //tyre front
  c = new Cylinder(48,tyre_radius,tyre_Width,glm::vec4(0.0,0.5,0.5,1.0));
  handle[9] = new csX75::HNode(handle[5],c->indices,c->vertices,c->verticesColor,c->normals,-1);
  handle[9]->setvaoLines(c->lineIndices,c->lineVertices,c->lineColor);
  handle[9]->change_parameters(0.50,0.0,(-0.5*rodLen),0.0,90.0,0.0);
  tyref = handle[9];

  // body frame : 
  c = new Cylinder(24,1.0,0.6,glm::vec4(0.7,0.7,0.7,1.0));
  bodyframe = new csX75::HNode(NULL,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  bodyframe->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);

  c = new Cylinder(24,0.20,4.0,glm::vec4(0.0,0.0,1.0,1.0));
  node2 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node2->change_parameters(-0.50,2.00,-0.50,70.0,0.0,0.0);

  c = new Cylinder(24,0.20,5.0,glm::vec4(0.0,0.0,1.0,1.0));
  node3 = new csX75::HNode(node2,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node3->change_parameters(0.0,1.50,-4.0,40.0,0.0,0.0);
  
  node4 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node4->change_parameters(-0.50,1.50,-2.0,20.0,0.0,0.0);

  c = new Cylinder(24,0.20,3.0,glm::vec4(0.0,0.0,1.0,1.0));
  node5 = new csX75::HNode(node4,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node5->change_parameters(0.0,1.50,-3.0,70.0,0.0,0.0);

  c = new Cylinder(24,0.20,4.5,glm::vec4(0.0,0.0,1.0,1.0));
  node6 = new csX75::HNode(node5,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node6->change_parameters(0.0,2.0,-2.0,70.0,0.0,0.0);

  c = new Cylinder(24,0.20,4.0,glm::vec4(0.0,0.0,1.0,1.0));
  node2 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node2->change_parameters(0.50,2.0,-0.50,70.0,0.0,0.0);

  c = new Cylinder(24,0.20,5.0,glm::vec4(0.0,0.0,1.0,1.0));
  node3 = new csX75::HNode(node2,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node3->change_parameters(0.0,1.50,-4.0,40.0,0.0,0.0);
  
  node4 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node4->change_parameters(0.50,1.50,-2.00,20.0,0.0,0.0);

  c = new Cylinder(24,.20,3.0,glm::vec4(0.0,0.0,1.0,1.0));
  node5 = new csX75::HNode(node4,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node5->change_parameters(0.0,1.50,-3.0,70.0,0.0,0.0);

  c = new Cylinder(24,0.20,4.5,glm::vec4(0.0,0.0,1.0,1.0));
  node6 = new csX75::HNode(node5,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node6->change_parameters(0.0,2.0,-2.0,70.0,0.0,0.0);

  Frustum * f = new Frustum(h,w,l,glm::vec4(1.0,0.0,0.0,1.0));
  engine = new csX75::HNode(NULL,f->indices,f->vc,f->verticesColor,f->normals,-1); 
  engine->change_parameters(-0.50,-1.50,-1.0,-90.0,0.0,0.0);
  
  c = new Cylinder(24,1.0,2.0,glm::vec4(0.0,0.0,1.0,1.0));
  node3 = new csX75::HNode(engine,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node3->change_parameters(1.0,0.50,1.50,90.0,0.0,0.0);

  //  connect the back tyre to the bike
  f = new Frustum(0.5,1.0,5.5,glm::vec4(0.5,0.5,0.5,1.0));
  node4 = new csX75::HNode(node3,f->indices,f->vc,f->verticesColor,f->normals,-1); 
  node4->change_parameters(0.0,-0.50,0.50,0.0,0.0,-25.0);

  c = new Cylinder(48,tyre_radius,tyre_Width,glm::vec4(0.0,0.5,0.5,1.0));
  node5 = new csX75::HNode(node4,c->indices,c->vertices,c->verticesColor,c->normals,-1);
  node5->setvaoLines(c->lineIndices,c->lineVertices,c->lineColor);
  node5->change_parameters(5.0,0.50,-0.50,0.0,0.0,0.0);
  tyreb = node5;

  // seat of the bike
  f = new Frustum(0.6,2.0,5.0,glm::vec4(0.3,0.3,0.1,1.0));
  node3 = new csX75::HNode(bodyframe,f->indices,f->vc,f->verticesColor,f->normals,f->tx_coords,tx,0); 
  node3->change_parameters(1.0,1.0,-1.0,0.0,0.0,90.0);

  // add bodyframe to engine
  engine->add_child(bodyframe);
  bodyframe->change_parameters(-1.50,0.50,4.20,0.0,0.0,-90.0);
  // add handle to body frame
  bodyframe->add_child(handlejoin);
  handlejoin->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);

  return engine;
}

//-----------------------------------------------------------------
