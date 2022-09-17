#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

void frameBuffer_size_callBack(GLFWwindow * w , int height , int width){
    glViewport(0,0,width,height);
}


void processInput(GLFWwindow *w){
    if(glfwGetKey(w,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(w,true);
    }
}


float vertices[] = {
0.0,0.0,0.0, //0
1.0,0.0,0.0,

0.50,0.0,0.0, //1
1.0,0.0,0.0,

0.75,0.0,0.0, //2
1.0,0.0,0.0,

1.0,0.0,0.0, //3
1.0,0.0,0.0,

0.0,1.0,0.0, //4
1.0,0.0,0.0
};

unsigned int indices[] = {
  0,4,
  1,4,
  2,4,
  3,4
};


int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(640,480,"Lets Grid",NULL,NULL);
    
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

    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);
    
    int status;
    char infoLog[512];

    unsigned int vs,fs,sp;

    const char * vsCode = "#version 330 core\n"
                            "layout (location = 0) in vec3 pos;\n"
                            "layout (location = 1) in vec3 posColor;\n"
                            "out vec4 posColorOut;\n"
                            "uniform mat4 model;"
                            "uniform mat4 view;"
                            "uniform mat4 projection;"
                            "void main(){\n"
                            "gl_Position = projection*view*model*vec4(pos.x, pos.y, pos.z, 1.0);\n"
                            " posColorOut = vec4(posColor.xyz, 1.0);\n"
                            "}\n\0";

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,&vsCode,NULL);
    glCompileShader(vs);

    glGetShaderiv(vs,GL_COMPILE_STATUS,&status);
    if(!status){
        glGetShaderInfoLog(vs,512,NULL,infoLog);
        std::cout<<"vs error: "<<infoLog<<std::endl;
    }  

    const char * fsCode = "#version 330 core\n"
                                 "in vec4 posColorOut ;\n" 
                                 "out vec4 FragColor;\n "
                                 "void main(){\n"
                                 "FragColor = vec4(1.0,1.0,0.0,0.0);\n"
                                 "}\n\0";    

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs,1,&fsCode,NULL);
    glCompileShader(fs);

    glGetShaderiv(fs,GL_COMPILE_STATUS,&status);
    if(!status){
        glGetShaderInfoLog(fs,512,NULL,infoLog);
        std::cout<<"fs error: "<<infoLog<<std::endl;
    }  

    sp = glCreateProgram();
    glAttachShader(sp,vs);
    glAttachShader(sp,fs);
    glLinkProgram(sp);
    
    glGetProgramiv(sp,GL_LINK_STATUS,&status);    
    if(!status){
        glGetProgramInfoLog(sp,512,NULL,infoLog);
        std::cout<<"link error : "<<infoLog<<std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);


    std::vector<glm::vec3> v;
    unsigned int gridlen;
    float x,y,z;
    gridlen=10;
    for(int i=0;i<=gridlen;i++){
        for(int j=0;j<=gridlen;j++){
            x=i*1.0/(gridlen+1);
            y=0.0;
            z=j*1.0/(gridlen+1);
            v.push_back(glm::vec3(x,y,z));
            v.push_back(glm::vec3(1.0,1.0,0.0));
            std::cout<<x<<"\t"<<y<<"\t"<<z<<std::endl;
        }
    }
    
    std::vector<glm::uvec2> vi;
    unsigned int p1,p2;
    std::cout<<"POints \n";
    for(int i=0;i<=gridlen;i++){
        p1=i;
        p2=(gridlen+1)*(gridlen)+i;

        std::cout<<p1<<"\t"<<p2<<"\n";
        vi.push_back(glm::uvec2(p1,p2));

        p1=i*(gridlen+1);
        p2=i*(gridlen+1)+gridlen;

        std::cout<<p1<<"\t"<<p2<<"\n";
        vi.push_back(glm::uvec2(p1,p2));
    }

    unsigned int total_points = vi.size()*2;
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,v.size()*sizeof(glm::vec3),v.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,vi.size()*sizeof(glm::uvec2),vi.data(),GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
  
    int modelLoc = glGetUniformLocation(sp, "model");
    int viewLoc = glGetUniformLocation(sp, "view");
    int projLoc = glGetUniformLocation(sp, "projection");
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    while(!glfwWindowShouldClose(window)){

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glUseProgram(sp);
 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(vao);
        
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,NULL);
        
        glfwSwapBuffers(window);    
        glfwPollEvents();
    }

    glfwTerminate();
 
    return 0;
}