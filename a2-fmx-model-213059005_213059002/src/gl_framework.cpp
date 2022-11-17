#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include "humanoid.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;

extern csX75::HNode* curr_node;
extern csX75::HNode* hip;
extern csX75::HNode* uLegR;
extern csX75::HNode* lLegR;
extern csX75::HNode* uLegL;
extern csX75::HNode* lLegL;
extern csX75::HNode* torso;
extern csX75::HNode* shoulder;
extern csX75::HNode* uArmR;
extern csX75::HNode* lArmR;
extern csX75::HNode* uArmL;
extern csX75::HNode* lArmL;
extern csX75::HNode* neck;
extern csX75::HNode* head;

extern csX75::HNode* tyref, *tyreb, *handlejoin, *engine , *bodyframe;
extern float handle_rot,tyref_rot,tyreb_rot;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LEQUAL);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && mods!=GLFW_MOD_SHIFT)
        curr_node = hip;
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && mods!=GLFW_MOD_SHIFT)
      curr_node = uLegR;
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && mods!=GLFW_MOD_SHIFT)
      curr_node = lLegR;
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && mods!=GLFW_MOD_SHIFT)
        curr_node = uLegL;
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
      curr_node = lLegL;
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
      curr_node = torso;
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
        curr_node = shoulder;
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
      curr_node = uArmR;
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
      curr_node = lArmR;
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
        curr_node = uArmL;
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
      curr_node = lArmL;
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
      curr_node = neck;
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
      curr_node = head;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        if(curr_node->dof_y)
            curr_node->dec_ry();
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        if(curr_node->dof_y)
            curr_node->inc_ry();
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        if(curr_node->dof_x)
            curr_node->dec_rx();
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        if(curr_node->dof_x)
            curr_node->inc_rx();
    }
    else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
    {
        if(curr_node->dof_z)
            curr_node->dec_rz();
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS)
    {
        if(curr_node->dof_z)
            curr_node->inc_rz();
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_yrot -= 10.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_yrot += 10.0;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xrot -= 10.0;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xrot += 10.0;
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zrot -= 10.0;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zrot += 10.0;   

    // bike-control
    else if (key == GLFW_KEY_Z  && action == GLFW_PRESS)
      handle_rot= (handle_rot-5.0) < -45.0 ? -45.0 : (handle_rot-5.0);   
    else if (key == GLFW_KEY_C  && action == GLFW_PRESS)
      handle_rot= (handle_rot+5.0) > 45.0 ? 45.0 : (handle_rot+5.0);   
    else if (key == GLFW_KEY_I  && action == GLFW_PRESS)
      tyref_rot-=5.0;
    else if (key == GLFW_KEY_O  && action == GLFW_PRESS)
      tyref_rot+=5.0;
    else if (key == GLFW_KEY_T  && action == GLFW_PRESS)
      tyreb_rot-=5.0;
    else if (key == GLFW_KEY_Y  && action == GLFW_PRESS)
      tyreb_rot+=5.0;
    else if (key == GLFW_KEY_N  && action == GLFW_PRESS)
      engine->dec_tx();
    else if (key == GLFW_KEY_M  && action == GLFW_PRESS)
      engine->inc_tx();
  }
};  
  


