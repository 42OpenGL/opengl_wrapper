#pragma once
#include <string>
#include <vector>

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <WRAPPER/ShaderProgram.hpp>

struct MeshVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct MeshTexture
{
	unsigned int	id;
	std::string		type;
	std::string		path;
};

class Mesh 
{
private :
	typedef std::vector<MeshVertex> 	vertices_t;
	typedef std::vector<GLuint>			indicies_t;
	typedef std::vector<MeshTexture> 	textures_t;
private:
	//  render data
	GLuint	_VAO, _VBO, _EBO;
	void setupMesh();
	vertices_t	vertices;
	indicies_t	indices;
	textures_t	textures;
public:
	// mesh data

	Mesh(vertices_t & vertices, indicies_t & indices, textures_t & textures);
	void Draw(const ShaderProgram & shaderprogram);
};

Mesh::Mesh(vertices_t & vertices, indicies_t & indices, textures_t & textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);  

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), 
					&indices[0], GL_STATIC_DRAW);

	// vertex positions0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);
	glEnableVertexAttribArray(0);	
	// vertex normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Normal));
	glEnableVertexAttribArray(1);	
	// vertex texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, TexCoords));
	glEnableVertexAttribArray(2);

	// HERE
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
	glBindVertexArray(0);
}

void Mesh::Draw(const ShaderProgram &shaderprogram)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for(GLuint i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if(name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if(name == "texture_specular")
			number = std::to_string(specularNr++);

		GLuint shaderID = shaderprogram.getShaderProgram();
		glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
} 