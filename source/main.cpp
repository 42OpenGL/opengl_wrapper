#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../include/WRAPPER/Shader.hpp"
#include "../include/WRAPPER/ShaderProgram.hpp"
#include "../include/WRAPPER/Window.hpp"

void key_manager(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

class Buffer
	{
		private:
			std::vector<Vertex> vertices = {
							{{ 0.5f,  0.5f,  0.0f}, {0.5f, 1.0f, 1.0f}},
							{{ 0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
							{{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
							{{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
						};
			std::vector<GLuint> indices =  {
							0, 1, 2,
							1, 2, 3,
						};
			GLuint vertex_array_obj;
			GLuint vertex_buffer_obj;
			GLuint element_buffer_obj;
		public:
			Buffer()
			{
				glGenVertexArrays(1, &vertex_array_obj);
				glGenBuffers(1, &vertex_buffer_obj);
				glGenBuffers(1, &element_buffer_obj);
				
				glBindVertexArray(vertex_array_obj);
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_obj);
				
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);
			}
			~Buffer()
			{
				glDeleteVertexArrays(1, &vertex_array_obj);
				glDeleteBuffers(1, &vertex_buffer_obj);
				glDeleteBuffers(1, &element_buffer_obj);
			}

			void setVertices(std::vector<Vertex> new_vertices)
			{
				this->vertices = new_vertices;
				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
			}

			void setIndices(std::vector<GLuint> new_indices)
			{
				this->indices = new_indices;
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);
			}
			
			GLuint getVAO()
			{
				return this->vertex_array_obj;
			}

			std::vector<GLuint> getIndices()
			{
				return this->indices;
			}
	};

	

int main_process()
{
    GLWindowWrapper window_instance;
    Shader          vertex_shader_instance(std::filesystem::path(ROOT_PATH) / "source/basic.vert", GL_VERTEX_SHADER);
    Shader          fragment_shader_instance(std::filesystem::path(ROOT_PATH) / "source/basic.frag", GL_FRAGMENT_SHADER);
    GLuint          vertex_shader_data = vertex_shader_instance.getShader();
    GLuint          fragment_shader_data = fragment_shader_instance.getShader();
    ShaderProgram   shaderprogram_instance(vertex_shader_data, fragment_shader_data);

	GLFWwindow* window = window_instance.getWindow();
	GLuint shader_program = shaderprogram_instance.getShaderProgram();

	Buffer			buffer_instance;

	std::vector<GLuint> new_indices = {
		0, 2, 1,
		1, 2, 3,
	};

	std::vector<Vertex> new_vertices = {
		{{ 0.5f,  0.5f,  0.0f}, {1.0f, 1.0f, 1.0f}},
		{{ 0.5f, -0.5f,  0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.0f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}},
	};

	
	buffer_instance.setIndices(new_indices);
	buffer_instance.setVertices(new_vertices);

	// 렌더링 루프
	while (!glfwWindowShouldClose(window))
	{
		key_manager(window);
		// 렌더링
		// 버퍼 초기화
		// 넘치면 1, 음수면 0으로 해줌
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 그리기
		glUseProgram(shader_program);
		glBindVertexArray(buffer_instance.getVAO());
		glDrawElements(GL_TRIANGLES, buffer_instance.getIndices().size(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader_program);
	glfwTerminate();
	return 0;
}

int main()
{
	try
	{
		return main_process();
	}
	catch(const std::exception& err)
	{
		std::cerr << err.what() << '\n';
		glfwTerminate();
		return -1;
	}
}
