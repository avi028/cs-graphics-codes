#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#define WIDTH 1000
#define HEIGHT 1000
#define GRID_SIZE 20


void frameBuffer_size_callBack(GLFWwindow * w , int width , int height){
    glViewport(0,0,width,height);
}


void processInput(GLFWwindow *w){
    if(glfwGetKey(w,GLFW_KEY_ESCAPE)==GLFW_PRESS){  
        glfwSetWindowShouldClose(w,true);
    }
}

float xr,yr,zr, cxr,cyr,czr , xt,yt,zt;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//!Close the window if the ESC key was pressed
if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    xr -= 1.0;
else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    xr += 1.0;
else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    yr += 1.0;
else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    yr -= 1.0;
else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
    zr += 1.0;
else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
    zr -= 1.0;
// else if (key == GLFW_KEY_P && action == GLFW_PRESS)
//     enable_perspective = !enable_perspective;   
else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
    xt -= 1.0;
else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
    xt += 1.0;
else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
    yt += 1.0;
else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
    yt -= 1.0;        
else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
    zt -= 1.0;
else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
    zt += 1.0;   
}


std::vector<glm::vec3> getCubeVertices(float l){
    std::vector<glm::vec3> v;
    
    //xy-b
    v.push_back(glm::vec3(0.0,0.0,0.0));
    v.push_back(glm::vec3(l,0.0,0.0));
    v.push_back(glm::vec3(l,l,0.0));
    v.push_back(glm::vec3(0.0,l,0.0));

    //xy-f
    v.push_back(glm::vec3(0.0,0.0,l));
    v.push_back(glm::vec3(l,0.0,l));
    v.push_back(glm::vec3(l,l,l));
    v.push_back(glm::vec3(0.0,l,l));

    //yx -l
    v.push_back(glm::vec3(0.0,0.0,0.0));
    v.push_back(glm::vec3(0.0,l,0.0));
    v.push_back(glm::vec3(0.0,l,l));
    v.push_back(glm::vec3(0.0,0.0,l));

    //yz -r
    v.push_back(glm::vec3(l,0.0,0.0));
    v.push_back(glm::vec3(l,l,0.0));
    v.push_back(glm::vec3(l,l,l));
    v.push_back(glm::vec3(l,0.0,l));

    //zx-d
    v.push_back(glm::vec3(0.0,0.0,0.0));
    v.push_back(glm::vec3(0.0,l,0.0));
    v.push_back(glm::vec3(l,0.0,l));
    v.push_back(glm::vec3(l,0.0,0.0));

    //zx-u
    v.push_back(glm::vec3(0.0,l,0.0));
    v.push_back(glm::vec3(0.0,l,l));
    v.push_back(glm::vec3(l,l,l));
    v.push_back(glm::vec3(l,l,0.0));

    return v;
}


unsigned int cubeIndices[]={
    0,1,2,
    2,3,0,

    4,5,6,
    6,7,4,

    8,9,10,
    10,11,8,

    12,13,14,
    14,15,12,

    16,17,18,
    18,19,16,

    20,21,22,
    22,23,20
};

void init(){
    xr=yr=zr=0.0;
    xr=35.0;
    yr=-45.0;
    xt=yt=zt=0.0;
}

float check(float *a){
    if(*a>=GRID_SIZE)
        *a=GRID_SIZE-1;
    else if(*a<0.0)
        *a=0.0;

    return *a;
}

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
    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window,frameBuffer_size_callBack);


    unsigned int vboxy,vboyz,vbozx,vaoxy,vaoyz,vaozx,ebo;
    unsigned int vaoCube,vboCube,eboCube;
    glGenVertexArrays(1,&vaoxy);
    glGenVertexArrays(1,&vaoyz);
    glGenVertexArrays(1,&vaozx);
    glGenVertexArrays(1,&vaoCube);
    glGenBuffers(1,&vboCube);
    glGenBuffers(1,&vboxy);
    glGenBuffers(1,&vboyz);
    glGenBuffers(1,&vbozx);
    glGenBuffers(1,&ebo);
    glGenBuffers(1,&eboCube);

    init();

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
    gridlen=GRID_SIZE;

    for(int i=0;i<=gridlen;i++){
        for(int j=0;j<=gridlen;j++){
            x=i*1.0/(gridlen+1);
            y=j*1.0/(gridlen+1);
            z=0*1.0/(gridlen+1);
            vxy.push_back(glm::vec3(x,y,z));
            vxy.push_back(glm::vec3(1.0,1.0,1.0));

            x=0*1.0/(gridlen+1);
            y=i*1.0/(gridlen+1);
            z=j*1.0/(gridlen+1);
            vyz.push_back(glm::vec3(x,y,z));
            vyz.push_back(glm::vec3(1.0,1.0,1.0));

            x=j*1.0/(gridlen+1);
            y=0*1.0/(gridlen+1);
            z=i*1.0/(gridlen+1);
            vzx.push_back(glm::vec3(x,y,z));
            vzx.push_back(glm::vec3(1.0,1.0,1.0));
        }
    }
    
    std::vector<glm::uvec2> vi;
    unsigned int p1,p2;
    // std::cout<<"POints \n";
    for(int i=0;i<=gridlen;i++){
        p1=i;
        p2=(gridlen+1)*(gridlen)+i;

        // std::cout<<p1<<"\t"<<p2<<"\n";
        vi.push_back(glm::uvec2(p1,p2));

        p1=i*(gridlen+1);
        p2=i*(gridlen+1)+gridlen;

        // std::cout<<p1<<"\t"<<p2<<"\n";
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


    // cube
    glBindVertexArray(vaoCube);
    glBindBuffer(GL_ARRAY_BUFFER,vboCube);
    std::vector<glm::vec3> vc= getCubeVertices(1.0/(gridlen+1));

    glBufferData(GL_ARRAY_BUFFER,vc.size()*sizeof(glm::vec3),vc.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,eboCube);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(cubeIndices),cubeIndices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glm::mat4 modelRotation = glm::mat4(1.0f);

    float c = (gridlen/2)*1.0/(gridlen+1);
    float glen = 1.0/(gridlen+1);

    glm::mat4 modelxy = glm::mat4(1.0f);
    // modelB = glm::rotate(modelB, glm::radians(-60.0f),glm::vec3(1.0f, 0.0f, 0.0f));
    modelxy = glm::translate(modelxy,glm::vec3(0.0,0.0,0.0));

    glm::mat4 modelyzl = glm::mat4(1.0f);
    // modelL = glm::rotate(modelL, glm::radians(45.0f),glm::vec3(0.0f, 1.0f, 0.0f));
    modelyzl = glm::translate(modelyzl,glm::vec3(0.0,0.0,0.0));

    glm::mat4 modelyzr = glm::mat4(1.0f);
    // modelR = glm::rotate(modelR, glm::radians(-45.0f),glm::vec3(0.0f, 1.0f, 0.0f));
    modelyzr = glm::translate(modelyzr,glm::vec3(2*c,0.0,0.0));

    glm::mat4 modelzx = glm::mat4(1.0f);
    // modelT = glm::rotate(modelT, glm::radians(-45.0f),glm::vec3(0.0f, 0.0f, 1.0f));
    modelzx = glm::translate(modelzx,glm::vec3(0.0,0.0,0.0));

    glm::mat4 modelCube = glm::mat4(1.0f);
    // modelT = glm::rotate(modelT, glm::radians(-45.0f),glm::vec3(0.0f, 0.0f, 1.0f));

    //glm::mat4(1.0f);//
    glm::mat4 view = glm::lookAt(glm::vec3(0.0,0.0,-3.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));;
    // note that we’re translating the scene in the reverse direction
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    //glm::mat4(1.0f);//

    glm::mat4 projection = glm::ortho(-1.0, 1.0, -1.0, 1.0, -6.0, 6.0);;
    // glm::mat4 projection =  glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 5.0);
    // projection = glm::perspective(glm::radians(45.0f), WIDTH.0f / HEIGHT.0f, 0.1f,100.0f);
    
  
    int modelLoc = glGetUniformLocation(sp, "model");
    int viewLoc = glGetUniformLocation(sp, "view");
    int projLoc = glGetUniformLocation(sp, "projection");
    
    while(!glfwWindowShouldClose(window)){

        modelRotation = glm::rotate(glm::mat4(1.0f),glm::radians(xr),glm::vec3(1.0f,0.0f,0.0f));
        modelRotation = glm::rotate(modelRotation,glm::radians(yr),glm::vec3(0.0f,1.0f,0.0f));
        modelRotation = glm::rotate(modelRotation,glm::radians(zr),glm::vec3(0.0f,0.0f,1.0f));

        
        modelCube = glm::translate(glm::mat4(1.0f),glm::vec3(check(&xt)/(gridlen+1),check(&yt)/(gridlen+1),check(&zt)/(gridlen+1)));
    
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        // glEnable(GL_LIGHTING);
        glUseProgram(sp);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelxy));
        glBindVertexArray(vaoxy);
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,0);

        // glEnable(GL_DEPTH_TEST);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelzx));
        glBindVertexArray(vaozx);
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,0);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelyzl));
        glBindVertexArray(vaoyz);
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,0);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelyzr));
        glBindVertexArray(vaoyz);
        glDrawElements(GL_LINES,total_points,GL_UNSIGNED_INT,0);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRotation*modelCube));
        glBindVertexArray(vaoCube);
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,NULL);


        // glDisable(GL_DEPTH_TEST);
        // glDisable(GL_LIGHTING);

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