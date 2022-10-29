#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/WRAPPER/Shader.hpp"
#include "../include/WRAPPER/ShaderProgram.hpp"
#include "../include/WRAPPER/Window.hpp"
#include "../include/WRAPPER/Buffer.hpp"

void key_manager(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main_process()
{
    GLWindowWrapper window_instance(600, 800, "hi");
    Shader          vertex_shader_instance(std::filesystem::path(ROOT_PATH) / "source/basic.vert", GL_VERTEX_SHADER);
    Shader          fragment_shader_instance(std::filesystem::path(ROOT_PATH) / "source/basic.frag", GL_FRAGMENT_SHADER);
    GLuint          vertex_shader_data = vertex_shader_instance.getShader();
    GLuint          fragment_shader_data = fragment_shader_instance.getShader();

	std::vector<GLuint> shaders_vector;
	shaders_vector.push_back(vertex_shader_data);
	shaders_vector.push_back(fragment_shader_data);
	ShaderProgram shaderprogram_instance(shaders_vector);

	GLFWwindow* window = window_instance.getWindow();
	GLuint shader_program = shaderprogram_instance.getShaderProgram();

	Buffer buffer_instance;

	// FOR TRANSLATE
	// glm::mat4 step = glm::mat4(1.0f);
	// glm::mat4 trans = glm::mat4(1.0f);
	// trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

	std::vector<GLuint> new_indices = {
		0, 2, 1,
		0, 3, 2,
	};

	std::vector<Vertex> new_vertices = {
		{{ 0.5f,  0.5f,  0.0f}, {1.0f, 1.0f, 1.0f}},
		{{ 0.5f, -0.5f,  0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.0f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}},
	};

	buffer_instance.setIndices(new_indices);
	buffer_instance.setVertices(new_vertices);

	// FOR ROTATE
	// glm::mat4 step = glm::mat4(1.0f);
	// 렌더링 루프
	while (!glfwWindowShouldClose(window))
	{
		key_manager(window);
		// 렌더링
		// 버퍼 초기화
		// 넘치면 1, 음수면 0으로 해줌
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		// FOR ROTATE
		// step = glm::rotate(step, (float)glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// GLuint location = glGetUniformLocation(shader_program, "step");
		// glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(step));

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
