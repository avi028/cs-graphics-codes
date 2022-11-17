#ifndef _CYLINDER_HPP
#define _CYLINDER_HPP

#include "gl_framework.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"


class Cylinder{
    
    public:
    
    const float PI = 3.1415926f;
    int indexCount;
    GLuint vbo,vao,ibo;
    int sector;
    float radius;
    float radius_front;
    float radius_back;
    float height;
    int baseVertex;
    int topVertex;
    glm::vec4 color;
    bool drawLine;
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec4> normals;
    std::vector<float> tx_croods;
    std::vector<glm::vec4> verticesColor;
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec4> lineVertices;
    std::vector<unsigned int> lineIndices;
    std::vector<glm::vec4> lineColor;


    Cylinder(int sector,float radius,float height,glm::vec4 color);
    Cylinder(int sector,float radius_front,float radius_back,float height,glm::vec4 color);
    void GenCylinder();
    void GenOffCylinder();
    void getLineVertices(int sectors, float radius,float height,glm::vec4 color,int step=1);
    void getLineIndices(int sectors,int step=1);
    void GenLines(glm::vec4 color,int step);

    void getIndices(int sectors);
    void getVertices(int sectors, float radius,float height,glm::vec4 color);
    void getOffVertices(int sectors, float radius_front,float radius_back,float height,glm::vec4 color);
    std::vector<float> getUnitVertices(int sectors);

    int getindexCountCylinder();

    void setPartialSectorIndices(int sectorCount);

};

#endif