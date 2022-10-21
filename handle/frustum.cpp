#include "frustum.hpp"


Frustum::Frustum(float h,float w,float l, glm::vec4 c){
    this->height = h;
    this->width = w;
    this->length= l;
    this->offset=0.0;    
    this->color = c;
    genFrustum();
}

void Frustum::getVertices()
{
    vc.push_back(glm::vec4(0.0,0.0,0.0,1.0)); //0
    this->verticesColor.push_back(color);
    vc.push_back(glm::vec4(length,0.0,0.0,1.0));//1
    this->verticesColor.push_back(color);
    vc.push_back(glm::vec4(length,width,0.0,1.0));//2
    this->verticesColor.push_back(color);
    vc.push_back(glm::vec4(0.0,width,0.0,1.0));//3
    this->verticesColor.push_back(color);
    vc.push_back(glm::vec4(0.0,0.0,height,1.0));//4
    this->verticesColor.push_back(color);   
    vc.push_back(glm::vec4(length,0.0,height,1.0));//5
    this->verticesColor.push_back(color);
    vc.push_back(glm::vec4(length,width,height,1.0));//6
    this->verticesColor.push_back(color);
    vc.push_back(glm::vec4(0.0,width,height,1.0));//7
    this->verticesColor.push_back(color);
}


void Frustum::getIndices(){
    indices.push_back(glm::uvec3(0,1,2));
    indices.push_back(glm::uvec3(2,3,0));

    indices.push_back(glm::uvec3(4,5,6));
    indices.push_back(glm::uvec3(6,7,4));

    indices.push_back(glm::uvec3(0,3,7));
    indices.push_back(glm::uvec3(7,4,0));

    indices.push_back(glm::uvec3(1,2,6));
    indices.push_back(glm::uvec3(6,5,1));

    indices.push_back(glm::uvec3(0,3,5));
    indices.push_back(glm::uvec3(5,1,0));

    indices.push_back(glm::uvec3(3,7,6));
    indices.push_back(glm::uvec3(6,2,3));
}


void Frustum::genFrustum(){
    getVertices();
    getIndices();
}