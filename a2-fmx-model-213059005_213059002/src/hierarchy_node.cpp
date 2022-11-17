#include "hierarchy_node.hpp"
#include "texture.hpp"

#include <iostream>

GLuint vPosition, vColor,vNormal,texCoord, uModelViewMatrix,normalMatrix,viewMatrix;

extern std::vector<glm::mat4> matrixStack;

namespace csX75
{	
	void HNode::getDefaultShader(){

			  // Load shaders and use the resulting shader program
			std::string vertex_shader_file("./src/vshader_normal.glsl");
			std::string fragment_shader_file("./src/fshader_normal.glsl");
			std::vector<GLuint> shaderList;
			shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
			shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

			shaderProgram = csX75::CreateProgramGL(shaderList);
			glUseProgram( shaderProgram );

			// getting the attributes from the shader program
			vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
			vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
			uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  			vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
  			normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
			uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
		    viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
	}

	void HNode::getTextureShader(){

			  // Load shaders and use the resulting shader program
			std::string vertex_shader_file("./src/vshader_texture.glsl");
			std::string fragment_shader_file("./src/fshader_texture.glsl");
			std::vector<GLuint> shaderList;
			shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
			shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

			shaderProgram = csX75::CreateProgramGL(shaderList);
			glUseProgram( shaderProgram );

			// getting the attributes from the shader program
			vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
			vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  			vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
  			texCoord = glGetAttribLocation( shaderProgram, "texCoord" ); 
  			normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
			uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
		    viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
	}
	/**
	 * @brief Construct a new HNode::HNode object
	 *
	 * @param a_parent
	 * @param num_v
	 * @param a_vertices
	 * @param a_colours
	 * @param v_size
	 * @param c_size
	 * @param ts
	 */

	HNode::HNode(HNode *a_parent, GLuint num_v, glm::vec4 *a_vertices, glm::vec4 *a_colours, std::size_t v_size, std::size_t c_size, bool ts = false)
	{
		forHuman = true;
		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		traingle_strip = ts;
		// get shader program
		getDefaultShader();

		// initialize vao and vbo of the object;

		// Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays(1, &vao);
		// Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers(1, &vbo);

		// bind them
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices);
		glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours);

		// setup the vertex array as per the shader
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		// set parent

		if (a_parent == NULL)
		{
			parent = NULL;
		}
		else
		{
			parent = a_parent;
			parent->add_child(this);
		}

		// initial parameters are set to 0;

		tx = ty = tz = rx = ry = rz = 0;

		update_matrices();
	}

	HNode::HNode(HNode *a_parent, GLuint num_v, std::vector<glm::vec4> &a_vertices, std::vector<glm::vec4> &a_colours, std::vector<GLuint> &a_indices, std::size_t v_size, std::size_t c_size, bool ts = false)
	{
		forTrack = true;
		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		traingle_strip = ts;
		// get shader program
		getDefaultShader();

		// initialize vao and vbo of the object;

		// Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays(1, &vao);
		// Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers(1, &vbo);

		// bind them
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, v_size + c_size, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, v_size, a_vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, v_size, c_size, a_colours.data());
		// setup the vertex array as per the shader
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		// Copy the points into the current buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_indices.size() * sizeof(GLuint), a_indices.data(), GL_STATIC_DRAW);

		// set parent

		if (a_parent == NULL)
		{
			parent = NULL;
		}
		else
		{
			parent = a_parent;
			parent->add_child(this);
		}

		// initial parameters are set to 0;

		tx = ty = tz = rx = ry = rz = 0;

		update_matrices();
	}

	/**
	 * @brief Construct a new HNode::HNode object
	 *
	 * @param a_parent
	 * @param indices
	 * @param vertices
	 * @param vertexColors
	 * @param drawLines
	 */
	HNode::HNode(HNode *a_parent, std::vector<glm::uvec3> indices, std::vector<glm::vec4> vertices, std::vector<glm::vec4> vertexColors,std::vector<glm::vec4> normals, GLuint shaderProgram)
	{

		// get shader program
		getDefaultShader();
		// initialize vao vbo and ibo
		hasIbo = true;
		// Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays(1, &vao);
		// Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers(1, &vbo);
		// Ask GL for a indidex Buffer Object (ibo)
		glGenBuffers(1, &ibo);

		this->drawLines = false;
		// bind them
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4) + vertexColors.size() * sizeof(glm::vec4)+normals.size() * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec4), vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertexColors.size() * sizeof(glm::vec4), vertexColors.data());
		glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4)+ vertexColors.size() * sizeof(glm::vec4), normals.size() * sizeof(glm::vec4), normals.data());

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::vec3), indices.data(), GL_STATIC_DRAW);

		// setup the vertex array as per the shader
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(glm::vec4)));

		//Normal
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(glm::vec4)+ vertexColors.size() * sizeof(glm::vec4)) );

		indicesCount = (int)indices.size() * 3;

		// set parent

		if (a_parent == NULL)
		{
			parent = NULL;
		}
		else
		{
			parent = a_parent;
			parent->add_child(this);
		}

		// initial parameters are set to 0;

		tx = ty = tz = rx = ry = rz = 0;
		update_matrices();
	}
	/**
	 * @brief Construct a new HNode::HNode object
	 * 
	 * @param a_parent 
	 * @param indices 
	 * @param vertexColors 
	 * @param normals 
	 * @param tx_coords 
	 * @param textureImg 
	 * @param shaderProgram 
	 */
	HNode::HNode(HNode* a_parent,std::vector<glm::uvec3> indices,std::vector<glm::vec4>vertices,std::vector<glm::vec4> vertexColors,std::vector<glm::vec4> normals,std::vector<float> tx_coords,std::string textureImg,GLuint shaderProgram)
	{
		if(shaderProgram==-1){
			getDefaultShader();
		}
		else{
			getTextureShader();
		}
		//has texture 
		hasTexture = true;
		tex=LoadTexture(textureImg.c_str(),256,256);

		// initialize vao vbo and ibo
		hasIbo = true;
		// Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays(1, &vao);
		// Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers(1, &vbo);
		// Ask GL for a indidex Buffer Object (ibo)
		glGenBuffers(1, &ibo);

		this->drawLines = drawLines;
		// bind them
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4) + vertexColors.size() * sizeof(glm::vec4) + normals.size()*sizeof(glm::vec4) + tx_coords.size()*sizeof(float), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec4), vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertexColors.size() * sizeof(glm::vec4), vertexColors.data());
		glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4)+ vertexColors.size() * sizeof(glm::vec4), normals.size() * sizeof(glm::vec4), normals.data());
		glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4)+ vertexColors.size() * sizeof(glm::vec4) + normals.size()*sizeof(glm::vec4), tx_coords.size() * sizeof(float), tx_coords.data());

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::vec3), indices.data(), GL_STATIC_DRAW);

		// setup the vertex array as per the shader
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		// colors
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(glm::vec4)));

		//Normal
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(glm::vec4)+ vertexColors.size() * sizeof(glm::vec4)) );

		//Textures
		glEnableVertexAttribArray( texCoord );
		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(glm::vec4)+ vertexColors.size() * sizeof(glm::vec4) + normals.size()*sizeof(glm::vec4)) );

		indicesCount = (int)indices.size() * 3;

		// set parent

		if (a_parent == NULL)
		{
			parent = NULL;
		}
		else
		{
			parent = a_parent;
			parent->add_child(this);
		}

		// initial parameters are set to 0;

		tx = ty = tz = rx = ry = rz = 0;
		update_matrices();
	}
	/**
	 * @brief update the matrix
	 *
	 */
	void HNode::update_matrices()
	{

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(tx, ty, tz));
	}

	/**
	 * @brief add child to parent
	 *
	 * @param a_child
	 */
	void HNode::add_child(HNode *a_child)
	{
		children.push_back(a_child);
	}

	/**
	 * @brief change the transform paremeters
	 *
	 * @param atx
	 * @param aty
	 * @param atz
	 * @param arx
	 * @param ary
	 * @param arz
	 */
	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz)
	{
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render()
	{

		// matrixStack multiply
		glm::mat4 view_matrix = matrixStack[0];
		glm::mat4 *ms_mult = multiply_stack(matrixStack);
  		glm::mat3 normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));

		glUseProgram(shaderProgram);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

		glBindVertexArray(vao);

		if(hasTexture){
		//   normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
		// glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
			glBindTexture(GL_TEXTURE_2D, tex);
			glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if(hasIbo)
		{
			glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);

			if (drawLines)
			{
				glBindVertexArray(vaoLines);
				glDrawElements(GL_LINES, lineIndicesCount, GL_UNSIGNED_INT, NULL);
			}
		}
		else if(forTrack)
		{
			glDrawElements(GL_TRIANGLE_STRIP, num_vertices, GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			if (!traingle_strip)
				glDrawArrays(GL_TRIANGLES, 0, num_vertices);
			else
				glDrawArrays(GL_TRIANGLE_STRIP, 0, num_vertices);
		}
		// for memory
		delete ms_mult;
	}

	void HNode::render_tree()
	{

		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();
	}

	void HNode::inc_rx()
	{
		rx += 5.0;
		update_matrices();
	}

	void HNode::inc_ry()
	{
		ry += 5.0;
		update_matrices();
	}

	void HNode::inc_rz()
	{
		rz += 5.0;
		update_matrices();
	}

	void HNode::dec_rx()
	{
		rx -= 5.0;
		update_matrices();
	}

	void HNode::dec_ry()
	{
		ry -= 5.0;
		update_matrices();
	}

	void HNode::dec_rz()
	{
		rz -= 5.0;
		update_matrices();
	}

	void HNode::inc_tx()
	{
		tx += 1.0;
		update_matrices();
	}

	void HNode::inc_ty()
	{
		ty += 1.0;
		update_matrices();
	}

	void HNode::inc_tz()
	{
		tz += 1.0;
		update_matrices();
	}

	void HNode::dec_tx()
	{
		tx -= 1.0;
		update_matrices();
	}

	void HNode::dec_ty()
	{
		ty -= 1.0;
		update_matrices();
	}

	void HNode::dec_tz()
	{
		tz -= 1.0;
		update_matrices();
	}

	/**
	 * @brief multiply the matrices in the stack
	 *
	 * @param matStack
	 * @return glm::mat4*
	 */
	glm::mat4 *multiply_stack(std::vector<glm::mat4> matStack)
	{
		glm::mat4 *mult;
		mult = new glm::mat4(1.0f);

		for (int i = 0; i < matStack.size(); i++)
		{
			*mult = (*mult) * matStack[i];
		}

		return mult;
	}
	/**
	 * @brief sets the x angle
	 *
	 * @param angle
	 */
	void HNode::set_rx(float angle)
	{
		rx = angle;
		update_matrices();
	}

	/**
	 * @brief sets the y angle
	 *
	 * @param angle
	 */
	void HNode::set_ry(float angle)
	{
		ry = angle;
		update_matrices();
	}

	/**
	 * @brief sets the z angle
	 *
	 * @param angle
	 */
	void HNode::set_rz(float angle)
	{
		rz = angle;
		update_matrices();
	}

	/**
	 * @brief sets the line vao for the given geometry
	 *
	 * @param indices
	 * @param vertexColors
	 */
	void HNode::setvaoLines(std::vector<unsigned int> indices, std::vector<glm::vec4> vertices, std::vector<glm::vec4> vertexColors)
	{
		// initialize vao vbo and ibo
		// Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays(1, &vaoLines);
		// Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers(1, &vboLines);
		// Ask GL for a indidex Buffer Object (ibo)
		glGenBuffers(1, &iboLines);

		// bind them
		glBindVertexArray(vaoLines);
		glBindBuffer(GL_ARRAY_BUFFER, vboLines);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboLines);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4) + vertexColors.size() * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec4), vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertexColors.size() * sizeof(glm::vec4), vertexColors.data());

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		// setup the vertex array as per the shader
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(glm::vec4)));
		lineIndicesCount = indices.size();
	}
}
