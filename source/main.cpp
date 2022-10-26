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

    // ShaderProgram   shaderprogram_instance;
	// shaderprogram_instance.putShader(vertex_shader_data);
	// shaderprogram_instance.putShader(fragment_shader_data);

	std::vector<GLuint> shaders_vector;
	shaders_vector.push_back(vertex_shader_data);
	shaders_vector.push_back(fragment_shader_data);
	ShaderProgram shaderprogram_instance(shaders_vector);

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
