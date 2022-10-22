/*
  CSX75 Tutorial on Hierarchical Modelling

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by - 
               Harshavardhan Kode
*/


#include "bike_model.hpp"
#include "cylinder.hpp"
#include "frustum.hpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
const int num_vertices = 36;


//-----------------------------------------------------------------


//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  // Handle + front tyre
  float rodLen = 60.0;
  float rodAngle = -20.0;
  float tyre_Width = 8.0;
  float tyre_radius = 25.0;

  Cylinder * c = new Cylinder(4,10.0,5.0,glm::vec4(1.0,1.0,0.0,1.0));
  handle[0] = new csX75::HNode(NULL,c->indices,c->vertices,c->verticesColor);
  handle[0]->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0f);
  handlejoin = handle[0];

  c = new Cylinder(24,2.0,20.0,glm::vec4(1.0,1.0,1.0,1.0));
  handle[1] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor);
  handle[1]->change_parameters(-13.0,0.0,4.0,0.0,120.0,0.0);

  handle[2] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor);
  handle[2]->change_parameters(13.0,0.0,4.0,0.0,60.0,0.0);

  c = new Cylinder(24,3.0,15.0,glm::vec4(0.0,1.0,1.0,1.0));
  handle[3] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor);
  handle[3]->change_parameters(-26.0,0.0,8.0,0.0,90.0,0.0);

  handle[4] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor);
  handle[4]->change_parameters(26.0,0.0,8.0,0.0,90.0,0.0);

  c = new Cylinder(24,2.0,rodLen,glm::vec4(0.0,0.0,1.0,1.0));
  handle[5] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor);
  handle[5]->change_parameters(-5.0,-12.0,-1*(rodLen/2.0),rodAngle,0.0,0.0);
  
  handle[6] = new csX75::HNode(handle[0],c->indices,c->vertices,c->verticesColor);
  handle[6]->change_parameters(5.0,-12.0,-1*(rodLen/2.0),rodAngle,0.0,0.0);

  //tyre front
  c = new Cylinder(48,tyre_radius,tyre_Width,glm::vec4(0.0,0.5,0.5,1.0),true);
  handle[7] = new csX75::HNode(handle[5],c->indices,c->vertices,c->verticesColor,true);
  handle[7]->setvaoLines(c->lineIndices,c->lineVertices,c->lineColor);
  handle[7]->change_parameters(5.0,0.0,(-0.5*rodLen),0.0,90.0,0.0);
  tyref = handle[7];

  // body frame : 
  c = new Cylinder(24,10,6,glm::vec4(0.7,0.7,0.7,1.0));
  bodyframe = new csX75::HNode(NULL,c->indices,c->vertices,c->verticesColor);
  bodyframe->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);

  c = new Cylinder(24,2.0,40,glm::vec4(0.0,0.0,1.0,1.0));
  node2 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor);
  node2->change_parameters(-5.0,20.0,-5.0,70.0,0.0,0.0);

  c = new Cylinder(24,2.0,50,glm::vec4(0.0,0.0,1.0,1.0));
  node3 = new csX75::HNode(node2,c->indices,c->vertices,c->verticesColor);
  node3->change_parameters(0.0,15.0,-40.0,40.0,0.0,0.0);
  
  node4 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor);
  node4->change_parameters(-5.0,15.0,-20.0,20.0,0.0,0.0);

  c = new Cylinder(24,2.0,30,glm::vec4(0.0,0.0,1.0,1.0));
  node5 = new csX75::HNode(node4,c->indices,c->vertices,c->verticesColor);
  node5->change_parameters(0.0,15.0,-30.0,70.0,0.0,0.0);

  c = new Cylinder(24,2.0,45,glm::vec4(0.0,0.0,1.0,1.0));
  node6 = new csX75::HNode(node5,c->indices,c->vertices,c->verticesColor);
  node6->change_parameters(0.0,20.0,-20.0,70.0,0.0,0.0);

  c = new Cylinder(24,2.0,40,glm::vec4(0.0,0.0,1.0,1.0));
  node2 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor);
  node2->change_parameters(5.0,20.0,-5.0,70.0,0.0,0.0);

  c = new Cylinder(24,2.0,50,glm::vec4(0.0,0.0,1.0,1.0));
  node3 = new csX75::HNode(node2,c->indices,c->vertices,c->verticesColor);
  node3->change_parameters(0.0,15.0,-40.0,40.0,0.0,0.0);
  
  node4 = new csX75::HNode(bodyframe,c->indices,c->vertices,c->verticesColor);
  node4->change_parameters(5.0,15.0,-20.0,20.0,0.0,0.0);

  c = new Cylinder(24,2.0,30,glm::vec4(0.0,0.0,1.0,1.0));
  node5 = new csX75::HNode(node4,c->indices,c->vertices,c->verticesColor);
  node5->change_parameters(0.0,15.0,-30.0,70.0,0.0,0.0);

  c = new Cylinder(24,2.0,45,glm::vec4(0.0,0.0,1.0,1.0));
  node6 = new csX75::HNode(node5,c->indices,c->vertices,c->verticesColor);
  node6->change_parameters(0.0,20.0,-20.0,70.0,0.0,0.0);

  // engine 
  float h,w,l;
  w=10;
  h=25;
  l=30;

  Frustum * f = new Frustum(h,w,l,glm::vec4(1.0,0.0,0.0,1.0));
  engine = new csX75::HNode(NULL,f->indices,f->vc,f->verticesColor); 
  engine->change_parameters(-5.0,-15.0,-10.0,-90.0,0.0,0.0);
  
  c = new Cylinder(24,10.0,20,glm::vec4(0.0,0.0,1.0,1.0));
  node3 = new csX75::HNode(engine,c->indices,c->vertices,c->verticesColor);
  node3->change_parameters(10.0,5.0,15.0,90.0,0.0,0.0);

  //  connect the back tyre to the bike
  f = new Frustum(5,10,55,glm::vec4(0.5,0.5,0.5,1.0));
  node4 = new csX75::HNode(node3,f->indices,f->vc,f->verticesColor); 
  node4->change_parameters(0.0,-5.0,5.0,0.0,0.0,-25.0);

  c = new Cylinder(48,tyre_radius,tyre_Width,glm::vec4(0.0,0.5,0.5,1.0),true);
  node5 = new csX75::HNode(node4,c->indices,c->vertices,c->verticesColor,true);
  node5->setvaoLines(c->lineIndices,c->lineVertices,c->lineColor);
  node5->change_parameters(50.0,5.0,-5.0,0.0,0.0,0.0);
  tyreb = node5;

  // seat of the bike
  f = new Frustum(6,20,50,glm::vec4(0.3,0.3,0.1,1.0));
  node3 = new csX75::HNode(bodyframe,f->indices,f->vc,f->verticesColor); 
  node3->change_parameters(10.0,10.0,-10.0,0.0,0.0,90.0);

  // add bodyframe to engine
  engine->add_child(bodyframe);
  bodyframe->change_parameters(-15.0,5.0,42.0,0.0,0.0,-90.0);
  // add handle to body frame
  bodyframe->add_child(handlejoin);
  handlejoin->change_parameters(0.0,0.0,10.0,0.0,0.0,0.0);

  root_node = curr_node = engine;
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  // if(enable_perspective)
  //   projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
  //   //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  // else
  unsigned int screenLen = 100;
  projection_matrix = glm::ortho(-1.0*screenLen, 1.0*screenLen, -1.0*screenLen, 1.0*screenLen, -1.0*screenLen, 1.0*screenLen);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);
  handlejoin->set_rz(handle_rot);
  tyref->set_rz(tyref_rot);
  tyreb->set_rz(tyreb_rot);

  root_node->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}
//-------------------------------------------------------------------------

