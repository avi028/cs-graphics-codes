#include <cmath>
#include <vector>
#include "cylinder.hpp"


/**
 * @brief Construct a new Cylinder:: Cylinder object
 * 
 * @param sector 
 * @param radius 
 * @param height 
 * @param color 
 * @param drawlines 
 */
Cylinder::Cylinder(int sector,float radius,float height,glm::vec4 color){
    this->sector = sector;
    this->radius = radius;
    this->height = height;
    this->color = color;
    this->GenCylinder();
}

/**
 * @brief Construct a new Cylinder:: Cylinder object
 * 
 * @param sector 
 * @param radius_front 
 * @param radius_back 
 * @param height 
 * @param color 
 */
Cylinder::Cylinder(int sector,float radius_front,float radius_back,float height,glm::vec4 color){
    this->sector = sector;
    this->radius_front = radius_front;
    this->radius_back = radius_back;
    this->height = height;
    this->color = color;
    this->GenOffCylinder();
}

/**
 * @brief get Index count
 * 
 * @return int 
 */
int Cylinder::getindexCountCylinder(){
    return indexCount;
}


/**
 * @brief Get the Vertices of the cylinder as per the radius and height
 * 
 * @param sectors 
 * @param radius 
 * @param height 
 * @param color
 * base center ........base side verties ........  top center vertex ....... top side vertices
 * 4 + 4 ............. sector*(4+4) .............. 4+4  .....................sector*(4+4).........
 * @return std::vector<glm::vec4> 
 */
void Cylinder::getLineVertices(int sectors, float radius,float height,glm::vec4 color,int step){
    std::vector<float> uv = getUnitVertices(sectors);

    for(int i=0;i<2;i++){
        float h = -height/2.0f  + i*height;
        float x,y,z;
        //  base center/top center 
        x=0.0;
        y=0.0;
        z=h;
        if(i==0)
            baseVertex = lineVertices.size();
        else
            topVertex = lineVertices.size();

        lineVertices.push_back(glm::vec4(x,y,z,1.0));
        lineColor.push_back(color);

        // side vertices 
        for(int j=0,uvItr=0;j<=sectors;j+=step){
            
            x = uv[uvItr++]*radius;
            y = uv[uvItr++]*radius;
            uvItr++;
            uvItr+=((step-1)*3);
            z = h;
            lineVertices.push_back(glm::vec4(x,y,z,1.0));
            lineColor.push_back(color);
        }
    }
}

/**
 * @brief Get line indices of the top and bottom circles
 * 
 * @param sectors 
 */

void Cylinder::getLineIndices(int sectors, int step){

    // bottom circle
    unsigned int k1= baseVertex ;// base center
    unsigned int k2;
    for (int i=1;i<=(sectors);i+=step){
        k2=k1+i;
        this->lineIndices.push_back(k1);
        this->lineIndices.push_back(k2);
    }                
    // topcircle
    k1=topVertex;
    for (int i=1;i<=(sectors);i+=step){
        k2=k1+i;
        this->lineIndices.push_back(k1);
        this->lineIndices.push_back(k2);
    }
}


/**
 * @brief Get the vertices of unit circle as per given sector
 * 
 * @param sectors 
 * @return std::vector<float> 
 */
std::vector<float> Cylinder::getUnitVertices(int sectors){
    float step = 2 * PI / sectors;
    float angle;

    std::vector<float> unitVertices;
    for(int i = 0; i <= sectors; ++i)
    {
        angle = i * step;
        unitVertices.push_back(cos(angle)); // x
        unitVertices.push_back(sin(angle)); // y
        unitVertices.push_back(0);  // z
    }
    return unitVertices;
}

/**
 * @brief Get the Vertices of the cylinder as per the radius and height
 * 
 * @param sectors 
 * @param radius 
 * @param height 
 * @param color
 * base center ........base side verties ........  top center vertex ....... top side vertices
 * 4 + 4 ............. sector*(4+4) .............. 4+4  .....................sector*(4+4).........
 * @return std::vector<glm::vec4> 
 */
void Cylinder::getVertices(int sectors, float radius,float height,glm::vec4 color){
    std::vector<float> uv = getUnitVertices(sectors);

    for(int i=0;i<2;i++){
        float h = -height/2.0f  + i*height;
        float x,y,z;
        //  base center/top center 
        x=0.0;
        y=0.0;
        z=h;
        
        float s,t;

        t= 0.5;
        s= 0.5;
        float nx=0.0,ny=0.0, nz = -1 + i * 2;  

        vertices.push_back(glm::vec4(x,y,z,1.0));
        this->verticesColor.push_back(color);
        normals.push_back(glm::vec4(nx,ny,nz,1.0));
        tx_croods.push_back(s);
        tx_croods.push_back(t);

        // side vertices 
        for(int j=0,uvItr=0;j<=sectors;j++){
            
            x = uv[uvItr++]*radius;
            y = uv[uvItr++]*radius;
            uvItr++;
            z = h;

            t = -x*s+t;
            s = -y*t+s;

            vertices.push_back(glm::vec4(x,y,z,1.0));
            verticesColor.push_back(color);
            normals.push_back(glm::vec4(nx,ny,nz,1.0));
            tx_croods.push_back(s);
            tx_croods.push_back(t);
        }
    }
    // side veritces
    for(int i=0;i<2;i++){
        float h = -height/2.0f  + i*height;
        float x,y,z;

        float s,t;
        t= i;
        s= 0;
        float nx=0.0,ny=0.0, nz = -1 + i * 2;  
        
        // side vertices
        for(int j=0,uvItr=0;j<=sectors;j++){
            
            x = uv[uvItr++]*radius;
            y = uv[uvItr++]*radius;
            uvItr++;
            z = h;

            nx = x;
            ny = y;
            nz = 0.0;

            s = ((float)(j*1.0))/sectors;

            vertices.push_back(glm::vec4(x,y,z,1.0));
            verticesColor.push_back(color);
            normals.push_back(glm::vec4(nx,ny,nz,1.0));
            tx_croods.push_back(s);
            tx_croods.push_back(t);
        }
    }
}

/**
 * @brief Get the Vertices of the cylinder as per the radius and height
 * 
 * @param sectors 
 * @param radius 
 * @param height 
 * @param color
 * base center ........base side verties ........  top center vertex ....... top side vertices
 * 4 + 4 ............. sector*(4+4) .............. 4+4  .....................sector*(4+4).........
 * @return std::vector<glm::vec4> 
 */
void Cylinder::getOffVertices(int sectors, float radius_front,float radius_back,float height,glm::vec4 color){
    std::vector<float> uv = getUnitVertices(sectors);

    for(int i=0;i<2;i++){
        float h = -height/2.0f  + i*height;
        float x,y,z;
        //  base center/top center 
        x=0.0;
        y=0.0;
        z=h;
        
        float s,t;

        t= 0.5;
        s= 0.5;
        float nx=0.0,ny=0.0, nz = -1 + i * 2;  

        vertices.push_back(glm::vec4(x,y,z,1.0));
        this->verticesColor.push_back(color);
        normals.push_back(glm::vec4(nx,ny,nz,1.0));
        tx_croods.push_back(s);
        tx_croods.push_back(t);
        float radius;
        if(i==0)
            radius = radius_front;
        else
            radius = radius_back;

        // side vertices 
        for(int j=0,uvItr=0;j<=sectors;j++){
            
            x = uv[uvItr++]*radius;
            y = uv[uvItr++]*radius;
            uvItr++;
            z = h;

            t = -x*s+t;
            s = -y*t+s;

            vertices.push_back(glm::vec4(x,y,z,1.0));
            verticesColor.push_back(color);
            normals.push_back(glm::vec4(nx,ny,nz,1.0));
            tx_croods.push_back(s);
            tx_croods.push_back(t);
        }
    }
    // side veritces
    for(int i=0;i<2;i++){
        float h = -height/2.0f  + i*height;
        float x,y,z;

        float s,t;
        t= i;
        s= 0;
        float nx=0.0,ny=0.0, nz = -1 + i * 2;  
        
        float radius;
        if(i==0)
            radius = radius_front;
        else
            radius = radius_back;

        // side vertices
        for(int j=0,uvItr=0;j<=sectors;j++){
            
            x = uv[uvItr++]*radius;
            y = uv[uvItr++]*radius;
            uvItr++;
            z = h;

            nx = x;
            ny = y;
            nz = 0.0;

            s = ((float)(j*1.0))/sectors;

            vertices.push_back(glm::vec4(x,y,z,1.0));
            verticesColor.push_back(color);
            normals.push_back(glm::vec4(nx,ny,nz,1.0));
            tx_croods.push_back(s);
            tx_croods.push_back(t);
        }
    }
}

/**
 * @brief Get the Indices vector
 * 
 * base center ........base side verties ........  top center vertex ....... top side vertices
 * 4 + 4 ............. sector*(4+4) .............. 4+4  .....................sector*(4+4).........
 * 
 * base circle incides ... side indices  .... top circle indices 
 * @param sectors 
 * @return std::vector<glm::vec3> 
 */
void Cylinder::getIndices(int sectors){
    int k1,k2,k3;

    // bottom circle
    k1= 0 ;// base center
    for (int i=1;i<=(sectors);i++){
        k2=k1+i+1;
        k3=k1+i;
        indices.push_back(glm::uvec3(k1,k2,k3));
    }                

    // topcircle
    k1=sectors+2;
    for (int i=1;i<=(sectors);i++){
        k2=k1+i;
        k3=k1+i+1;
        indices.push_back(glm::uvec3(k1,k2,k3));
    }   

    // sides
    // int base_index=1;
    // int top_index=sectors+3;
    int base_index=1 + sectors+1 + 1 + sectors+1;
    int top_index= base_index + sectors+1;
    
    for (int i=0;i<=(sectors-1);i++){

        // triangle 1
        k1=base_index+i;
        k2=k1+1;
        k3=top_index+i;
        indices.push_back(glm::uvec3(k1,k2,k3));

        // triangle 2
        k1=top_index+i;
        k2=k2;
        k3=k1+1;
        indices.push_back(glm::uvec3(k1,k2,k3));            
    }   

    this->indexCount = indices.size()*3;
}

void Cylinder::setPartialSectorIndices(int sectorCount){
    // get the indices of the triangle to particular sector counter
    indices.clear();
    int k1,k2,k3;

    // bottom circle
    k1= 0 ;// base center
    for (int i=1;i<=(sectorCount);i++){
        k2=k1+i+1;
        k3=k1+i;
        indices.push_back(glm::uvec3(k1,k2,k3));
    }                

    // topcircle
    k1=sector+2;
    for (int i=1;i<=(sectorCount);i++){
        k2=k1+i;
        k3=k1+i+1;
        indices.push_back(glm::uvec3(k1,k2,k3));
    }   

    // sides
    int base_index=1;
    int top_index=sector+3;
    
    for (int i=0;i<=(sectorCount-1);i++){

        // triangle 1
        k1=base_index+i;
        k2=k1+1;
        k3=top_index+i;
        indices.push_back(glm::uvec3(k1,k2,k3));

        // triangle 2
        k1=top_index+i;
        k2=k2;
        k3=k1+1;
        indices.push_back(glm::uvec3(k1,k2,k3));            
    }   

    this->indexCount = indices.size()*3;
}

/**
 * @brief Generates vertices and indices of the cylinder
 * 
 */
void Cylinder::GenCylinder(){

    /**Vertex Data*/
    getVertices(sector,radius,height,color);

    /**Vertex index*/
    getIndices(sector);    
}

/**
 * @brief Generates vertices and indices of the cylinder
 * 
 */
void Cylinder::GenOffCylinder(){

    /**Vertex Data*/
    getOffVertices(sector,radius_front,radius_back,height,color);

    /**Vertex index*/
    getIndices(sector);    
}

void Cylinder::GenLines(glm::vec4 color, int step){

    this->getLineVertices(sector,radius,height,color,step);
    this->getLineIndices(this->sector,step);
}
