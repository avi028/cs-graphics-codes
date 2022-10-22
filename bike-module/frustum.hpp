#ifndef _FRUSTUM_HPP
#define _FRUSTUM_HPP

#include "gl_framework.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class Frustum{

    float height;
    float length;
    float width;
    float offset;

    GLuint vbo,vao,ibo;

    glm::vec4 color;

    public:

    std::vector<glm::vec4> vc;
    std::vector<glm::vec4> verticesColor;
    std::vector<glm::uvec3> indices;

    Frustum(float h,float w,float l,glm::vec4 color);
    void getVertices();
    void getIndices();
    void genFrustum();

};

#endif