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
    int baseVertex;
    int topVertex;
    glm::vec4 color;
    bool drawLine;
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec4> verticesColor;
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec4> lineVertices;
    std::vector<unsigned int> lineIndices;
    std::vector<glm::vec4> lineColor;
    
    Cylinder(int sector,float radius,float height,glm::vec4 color,bool drawLines=false);
    void GenCylinder();
    void GenLines(glm::vec4 color,int step);

    void getLineVertices(int sectors, float radius,float height,glm::vec4 color,int step=1);
    void getLineIndices(int sectors,int step=1);

    void getIndices(int sectors);
    void getVertices(int sectors, float radius,float height,glm::vec4 color);
    std::vector<float> getUnitVertices(int sectors);
    int getindexCountCylinder();
};

#endif