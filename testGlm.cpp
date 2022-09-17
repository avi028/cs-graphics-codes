#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


int main(){
    glm::vec4  vec(1.0f, 1.0f, 0.0f, 1.0f);
    glm::vec4  vecOut(1.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 trans = glm::mat4(1.0f);
    trans  =  glm::translate (trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vecOut = trans*vec;
    std::cout<<vecOut.x<<"\t"<<vecOut.y<<"\t"<<vecOut.z<<std::endl;


    trans = glm::mat4(1.0f);
    trans = glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0,1.0,0.0));
    vecOut = trans*vec;
    std::cout<<vecOut.x<<"\t"<<vecOut.y<<"\t"<<vecOut.z<<std::endl;

    trans = glm::mat4(1.0f);
    trans = glm::scale(trans,glm::vec3(0.5,0.5,1.0));
    vecOut = trans*vec;
    std::cout<<vecOut.x<<"\t"<<vecOut.y<<"\t"<<vecOut.z<<std::endl;



    return 0;
}

