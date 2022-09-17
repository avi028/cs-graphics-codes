#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#define WIDTH 1080
#define HEIGHT 720

void frameBuffer_size_callBack(GLFWwindow * w , int height , int width){
    glViewport(0,0,width,height);
}


void processInput(GLFWwindow *w){
    if(glfwGetKey(w,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(w,true);
    }
}




// float xy[] = {
// 0.5f, 0.5f, 0.0f, // top right
// 1.0f, 1.0f, 0.1f,
// 0.5f, -0.5f, 0.0f, // bottom right
// 1.0f, 1.0f, 0.1f,
// -0.5f, -0.5f, 0.0f, // bottom left
// 1.0f, 1.0f, 0.1f,
// -0.5f, 0.5f, 0.0f, // top left
// 1.0f, 1.0f, 0.1f,
// };


// float yz[] = {
// 0.0f, 0.5f, 0.5f, // top right
// 1.0f, 0.0f, 0.1f,
// 0.0f, -0.5f, 0.5f, // bottom right
// 1.0f, 0.0f, 0.1f,
// 0.0f, -0.5f, -0.5f, // bottom left
// 1.0f, 0.0f, 0.1f,
// 0.0f, 0.5f, -0.5f, // top left
// 1.0f, 0.0f, 0.1f
// };

// float zx[] = {
// 0.5f, 0.0f, 0.5f, // top right
// 0.0f, 1.0f, 0.1f,
// 0.5f, 0.0f, -0.5f, // bottom right
// 0.0f, 1.0f, 0.1f,
// -0.5f, 0.0f, -0.5f, // bottom left
// 0.0f, 1.0f, 0.1f,
// -0.5f, 0.f, 0.5f, // top left
// 0.0f, 1.0f, 0.1f
// };

// unsigned int vertexIndices[] = { // note that we start from 0!
// 0, 1, 2, // first triangle
// 2, 3, 0 // second triangle
// };



int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(WIDTH,HEIGHT,"Going 3D",NULL,NULL);
    
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

    glViewport(0,0,WIDTH,HEIGHT);
    glfwSetFramebufferSizeCallback(window,frameBuffer_size_callBack);


    unsigned int vboxy,vboyz,vbozx,vaoxy,vaoyz,vaozx,ebo;

    glGenVertexArrays(1,&vaoxy);
    glGenVertexArrays(1,&vaoyz);
    glGenVertexArrays(1,&vaozx);
    glGenBuffers(1,&vboxy);
    glGenBuffers(1,&vboyz);
    glGenBuffers(1,&vbozx);
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
                                 "FragColor = posColorOut;\n"
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

    std::vector<glm::vec3> vxy;
    std::vector<glm::vec3> vyz;
    std::vector<glm::vec3> vzx;
    unsigned int gridlen;
    float x,y,z;
    gridlen=100;
    for(int i=0;i<=gridlen;i++){
        for(int j=0;j<=gridlen;j++){
            x=i*1.0/(gridlen+1);
            y=j*1.0/(gridlen+1);
            z=0*1.0/(gridlen+1);
            vxy.push_back(glm::vec3(x,y,z));
            vxy.push_back(glm::vec3(1.0,1.0,0.0));

            x=0*1.0/(gridlen+1);
            y=i*1.0/(gridlen+1);
            z=j*1.0/(gridlen+1);
            vyz.push_back(glm::vec3(x,y,z));
            vyz.push_back(glm::vec3(1.0,0.0,0.0));

            x=j*1.0/(gridlen+1);
            y=0*1.0/(gridlen+1);
            z=i*1.0/(gridlen+1);
            vzx.push_back(glm::vec3(x,y,z));
            vzx.push_back(glm::vec3(1.0,1.0,1.0));
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


    // xy 
    glBindVertexArray(vaoxy);
    glBindBuffer(GL_ARRAY_BUFFER,vboxy);
    glBufferData(GL_ARRAY_BUFFER,vxy.size()*sizeof(glm::vec3),vxy.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,vi.size()*sizeof(glm::uvec2),vi.data(),GL_STATIC_DRAW);
 
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // yz
    glBindVertexArray(vaoyz);
    glBindBuffer(GL_ARRAY_BUFFER,vboyz);
    glBufferData(GL_ARRAY_BUFFER,vyz.size()*sizeof(glm::vec3),vyz.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,vi.size()*sizeof(glm::uvec2),vi.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // zx
    glBindVertexArray(vaozx);
    glBindBuffer(GL_ARRAY_BUFFER,vbozx);
    glBufferData(GL_ARRAY_BUFFER,vzx.size()*sizeof(glm::vec3),vzx.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,vi.size()*sizeof(glm::uvec2),vi.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glm::mat4 modelRotation = glm::mat4(1.0f);
    modelRotation = glm::rotate(modelRotation,glm::radians(35.0f),glm::vec3(1.0f,0.0f,0.0f));
    modelRotation = glm::rotate(modelRotation,glm::radians(-45.0f),glm::vec3(0.0f,1.0f,0.0f));


    glm::mat4 modelxy = glm::mat4(1.0f);
    // modelB = glm::rotate(modelB, glm::radians(-60.0f),glm::vec3(1.0f, 0.0f, 0.0f));
    float c = (gridlen/2)*1.0/(gridlen+1);

    modelxy = glm::translate(modelxy,glm::vec3(-c,-c,-c));

    glm::mat4 modelyzl = glm::mat4(1.0f);
    // modelL = glm::rotate(modelL, glm::radians(45.0f),glm::vec3(0.0f, 1.0f, 0.0f));
    modelyzl = glm::translate(modelyzl,glm::vec3(-c,-c,-c));

    glm::mat4 modelyzr = glm::mat4(1.0f);
    // modelR = glm::rotate(modelR, glm::radians(-45.0f),glm::vec3(0.0f, 1.0f, 0.0f));
    modelyzr = glm::translate(modelyzr,glm::vec3(-c,-c,-c));

    glm::mat4 modelzx = glm::mat4(1.0f);
    // modelT = glm::rotate(modelT, glm::radians(-45.0f),glm::vec3(0.0f, 0.0f, 1.0f));
    modelzx = glm::translate(modelzx,glm::vec3(-c,-c,-c));

    //glm::mat4(1.0f);//
    glm::mat4 view = glm::lookAt(glm::vec3(0.0,0.0,-2.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));;
    // note that we’re translating the scene in the reverse direction
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    //glm::mat4(1.0f);//

    glm::mat4 projection = glm::ortho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);;
//    glm::mat4 projection =  glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 5.0);
    // projection = glm::perspective(glm::radians(45.0f), WIDTH.0f / HEIGHT.0f, 0.1f,100.0f);
    
  
    int modelLoc = glGetUniformLocation(sp, "model");
    int viewLoc = glGetUniformLocation(sp, "view");
    int projLoc = glGetUniformLocation(sp, "projection");
    
    while(!glfwWindowShouldClose(window)){

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glUseProgram(sp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelxy));
        glBindVertexArray(vaoxy);
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,0);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelyzl));
        glBindVertexArray(vaoyz);
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,0);

        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelyzr));
        // glBindVertexArray(vaoyz);
        // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelzx));
        glBindVertexArray(vaozx);
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,0);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        glfwSwapBuffers(window);    
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vaoxy);
    glDeleteVertexArrays(1, &vaoyz);
    glDeleteVertexArrays(1, &vaozx);
    glDeleteBuffers(1, &vboxy);
    glDeleteBuffers(1, &vboyz);
    glDeleteBuffers(1, &vbozx);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(sp);   
    glfwTerminate();
 
    return 0;
}