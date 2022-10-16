#include "hierarchy_node.hpp"

#include <iostream>

extern GLuint vPosition,vColor,uModelViewMatrix;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, std::vector<glm::uvec3> indices,std::vector<glm::vec4>vertices,std::vector<glm::vec4> vertexColors){

		// initialize vao vbo and ibo
		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);
		//Ask GL for a indidex Buffer Object (ibo)
		glGenBuffers(1,&ibo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);

		glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(glm::vec4) + vertexColors.size()*sizeof(glm::vec4),NULL,GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(glm::vec4),vertices.data());
		glBufferSubData( GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec4), vertexColors.size()*sizeof(glm::vec4), vertexColors.data() );
   		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(glm::vec3),indices.data(),GL_STATIC_DRAW);

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size()*sizeof(glm::vec4)));

		indicesCount= indices.size()*3;

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));
	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);
	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glBindVertexArray (vao);
		//glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    	glDrawElements(GL_TRIANGLES,indicesCount,GL_UNSIGNED_INT,NULL);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx++;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry++;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz++;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx--;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry--;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz--;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}