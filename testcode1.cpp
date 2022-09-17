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


// float vertices[] = {
// -0.25f, 0.0f, 0.0f, // t1
// -0.5f, 0.0f, 0.0f, // t1
// -0.375f, 0.25f, 0.0f, // t1
// 0.25f, 0.0f, 0.0f, // t2
// 0.5f, 0.0f, 0.0f, // t2
// 0.375f, 0.25f, 0.0f, // t2
// };

float vertices1[]={
-0.25f, 0.0f, 0.0f, // t1
1.0f,0.0f,0.0f,//c1
-0.5f, 0.0f, 0.0f, // t1
0.0f,1.0f,0.0f,//c2
-0.375f, -0.25f, 0.0f, // t1
0.0f,0.0f,1.0f,//c3
};

float vertices2[]={
0.25f, 0.0f, 0.0f, // t2
0.5f, 0.0f, 0.0f, // t2
0.375f, 0.25f, 0.0f, // t2
};

unsigned int indices[] = { // note that we start from 0!
0, 1, 2, // first triangle
3, 4, 5 // second triangle
};

int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(640,480,"Test Code 1",NULL,NULL);
    
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
    
    unsigned int vbo;
    unsigned int vbo1;
    unsigned int vbo2;
    unsigned int vao;
    unsigned int vao1;
    unsigned int vao2;
    unsigned int ebo;

    glGenBuffers(1,&ebo);
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);

    glGenVertexArrays(1,&vao1);
    glGenVertexArrays(1,&vao2);
    glGenBuffers(1,&vbo2);
    glGenBuffers(1,&vbo1);

    int status;
    char infoLog[512];

    unsigned int vertexShader1;
    unsigned int vertexShader2;

    unsigned int fragmentShader1;
    unsigned int fragmentShader2;


    const char * vertexSCode1 = "#version 330 core\n"
                                "layout (location = 0) in vec3 pos;\n"
                                "layout (location = 1) in vec3 vertexColorIn;\n"
                                "out vec4 vertexColorOut;\n"
                                "void main(){\n"
                                "gl_Position = vec4(pos.xyz, 1.0);\n" // swizziling 
                                "vertexColorOut = vec4(vertexColorIn.xyz, 1.0);\n"
                                "}\n";
    vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader1,1,&vertexSCode1,NULL);

    glCompileShader(vertexShader1);
    glGetShaderiv(vertexShader1,GL_COMPILE_STATUS,&status);

    if(!status){
        glGetShaderInfoLog(vertexShader1,sizeof(infoLog),NULL,infoLog);
        std::cout<<"Compilation Failed vertex shader 1 \n" <<infoLog<<"\n";

    }


    const char * fragmentSCode1 = "#version 330 core\n"
                                 "out vec4 FragColor;\n "
                                 "in vec4 vertexColorOut;\n"
                                 "void main(){\n"
                                 "FragColor = vertexColorOut;\n"
                                 "}\n";    
    
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1,1,&fragmentSCode1,NULL);
    glCompileShader(fragmentShader1);
    glGetShaderiv(fragmentShader1,GL_COMPILE_STATUS,&status);
    if(!status){
        glGetShaderInfoLog(fragmentShader1,sizeof(infoLog),NULL,infoLog);
        std::cout<<"Compilation Failed fragment shader \n" <<infoLog<<"\n";
        
    }


    const char * vertexSCode2 = "#version 330 core\n"
                                "layout (location = 0) in vec3 pos;\n"
                                "uniform vec2 shiftVec;\n"
                                "uniform mat4 transform;\n"
                                "out vec4 vertexColorOut;\n"
                                "void main(){\n"
                                "gl_Position = transform*vec4(pos.x+shiftVec.x, pos.y+shiftVec.y, pos.z, 1.0);\n" // swizziling 
                                " vertexColorOut = gl_Position;\n"
                                "}\n";
    vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2,1,&vertexSCode2,NULL);

    glCompileShader(vertexShader2);

    glGetShaderiv(vertexShader2,GL_COMPILE_STATUS,&status);
    if(!status){
        glGetShaderInfoLog(vertexShader2,sizeof(infoLog),NULL,infoLog);
        std::cout<<"Compilation Failed vertex shader 2 \n" <<infoLog<<"\n";

    }

    const char * fragmentSCode2 = "#version 330 core\n"
                                 "out vec4 FragColor;\n "
                                 "in vec4 vertexColorOut;\n"
                                 "void main(){\n"
                                 "FragColor = vertexColorOut;\n"
                                 "}\n";    
    
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentSCode2,NULL);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2,GL_COMPILE_STATUS,&status);
    if(!status){
        glGetShaderInfoLog(fragmentShader2,sizeof(infoLog),NULL,infoLog);
        std::cout<<"Compilation Failed fragment shader 2\n" <<infoLog<<"\n";
        
    }


    unsigned int shaderProgram1;
    unsigned int shaderProgram2;

    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1,vertexShader1);
    glAttachShader(shaderProgram1,fragmentShader1);
    glLinkProgram(shaderProgram1);

    glGetProgramiv(shaderProgram1,GL_LINK_STATUS,&status);
    if(!status){
        glGetProgramInfoLog(shaderProgram1,sizeof(infoLog),NULL,infoLog);
        std::cout<<"Linking Failed 1: \n" <<infoLog<<"\n";

    }

    glDeleteShader(fragmentShader1);
    glDeleteShader(vertexShader1);

    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader2);
    glAttachShader(shaderProgram2,fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2,GL_LINK_STATUS,&status);
    if(!status){
        glGetProgramInfoLog(shaderProgram2,sizeof(infoLog),NULL,infoLog);
        std::cout<<"Linking Failed 2: \n" <<infoLog<<"\n";

    }

    glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShader2);


    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER,vbo1);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glEnableVertexAttribArray(0);

    
    int count=0;
    while(!glfwWindowShouldClose(window)){

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(vao1);
        // if(count%2==0){
        //     glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        //     count=1;
        // }
        // else{
        //     glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        //     count=2;
        // }
        glDrawArrays(GL_TRIANGLES,0,3);
        // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        unsigned int transformLoc = glGetUniformLocation(shaderProgram2,"transform");        
        int shiftVecLocation = glGetUniformLocation(shaderProgram2,"shiftVec");

        glUseProgram(shaderProgram2);

        glUniform2f(shiftVecLocation,0.0f,0.0f);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans,glm::radians(count*1.0f),glm::vec3(0.0,0.0,1.0));
        trans = glm::scale(trans,glm::vec3(count*0.01f,count*0.01f,0.0));
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(trans));
        count+=1;

        glBindVertexArray(vao2);
        // if(count%2==0){
        //     glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        //     count=1;
        // }
        // else{
        //     glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        //     count=2;
        // }
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);    
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
