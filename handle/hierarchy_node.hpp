#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz;

		GLuint vao,vbo,ibo;

		glm::mat4 rotation;
		glm::mat4 translation;

		int indicesCount;
		
		std::vector<HNode*> children;
		HNode* parent;

		void update_matrices();

	  public:
		HNode (HNode* parent,std::vector<glm::uvec3> indices,std::vector<glm::vec4>vertices,std::vector<glm::vec4> vertexColors);
		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif