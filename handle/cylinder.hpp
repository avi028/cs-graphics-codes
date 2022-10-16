#ifndef _CYLINDER_HPP
#define _CYLINDER_HPP

#include "gl_framework.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

const float PI = 3.1415926f;

class Cylinder{
    
    public:
    
    int indexCount;
    GLuint vbo,vao,ibo;
    int sector;
    float radius;
    float height;
    glm::vec4 color;

    std::vector<glm::vec4> vertices;
    std::vector<glm::vec4> verticesColor;
    std::vector<glm::uvec3> indices;

    Cylinder(int sector,float radius,float height,glm::vec4 color);
    void GenCylinder();
    void getIndices(int sectors);
    void getVertices(int sectors, float radius,float height,glm::vec4 color);
    std::vector<float> getUnitVertices(int sectors);
    int getindexCountCylinder();
};

#endif