#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader_util.hpp"

#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz;
        
		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;

		glm::mat4 rotation;
		glm::mat4 translation;
        bool traingle_strip=false;
		bool hasIbo=false;
		bool forHuman=false;
		bool forTrack=false;
		bool hasTexture=false;
		std::vector<HNode*> children;
		HNode* parent;
		
		//addon 
		int indicesCount;
		int lineIndicesCount ; 
		GLuint ibo;
		GLuint vaoLines,vboLines,iboLines;
		bool drawLines=false;
		GLuint shaderProgram;
		GLuint tex;
	//---------------------------------------------------------------------
		void update_matrices();

	  public:
        bool dof_x=true,dof_y=true,dof_z=true;

		HNode (HNode* parent,std::vector<glm::uvec3> indices,std::vector<glm::vec4>vertices,std::vector<glm::vec4> vertexColors,std::vector<glm::vec4> normals,std::vector<float> tx_coords,std::string textureImg,GLuint shaderProgram=-1);
		HNode (HNode* parent,std::vector<glm::uvec3> indices,std::vector<glm::vec4>vertices,std::vector<glm::vec4> vertexColors,std::vector<glm::vec4> normals,GLuint shaderProgram=-1);

		HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, std::size_t, std::size_t,bool);
		HNode (HNode*, GLuint, std::vector<glm::vec4>&,  std::vector<glm::vec4>&,std::vector<GLuint>&, std::size_t, std::size_t,bool);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();

		void inc_tx();
		void inc_ty();
		void inc_tz();
		void dec_tx();
		void dec_ty();
		void dec_tz();

		void set_rx(float angle);
		void set_ry(float angle);
		void set_rz(float angle);
        float get_rx();
        float get_ry();
        float get_rz();
		void setvaoLines(std::vector<unsigned int> indices,std::vector<glm::vec4>vertices,std::vector<glm::vec4> vertexColors);
		void setShaderProgram();
		void getDefaultShader();
		void getTextureShader();

	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif
