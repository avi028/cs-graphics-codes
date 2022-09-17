#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void frameBuffer_size_callBack(GLFWwindow * w , int height , int width){
    glViewport(0,0,width,height);
}


void processInput(GLFWwindow *w){
    if(glfwGetKey(w,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(w,true);
    }
}


int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(640,480,"Going 3D",NULL,NULL);
    
    if(window == NULL){
        std::cout<<"Failed to initialise the window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;

    GLenum glew_init_error = glewInit();
    if( GLEW_OK != glew_init_error){
        std::cout<<"Failed to start the glew library \n";
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,640,480);
    glfwSetFramebufferSizeCallback(window,frameBuffer_size_callBack);


    unsigned int vbo,vao,ebo;

    while(!glfwWindowShouldClose(window)){

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);    
        glfwPollEvents();
    }

    glfwTerminate();
 
    return 0;
}