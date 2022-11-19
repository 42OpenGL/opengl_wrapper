#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/WRAPPER/Shader.hpp"
#include "../include/WRAPPER/ShaderProgram.hpp"
#include "../include/WRAPPER/Window.hpp"
#include "../include/WRAPPER/Buffer.hpp"
#include "../include/WRAPPER/Camera.hpp"

// 3d model loading
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Camera	camera_instance(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

void key_manager(GLFWwindow *window)
{
	float step = 0.042;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_instance.move_up();
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_instance.move_left();
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_instance.move_right();
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_instance.move_down();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera_instance.move_forward();
		else
			camera_instance.move_backward();
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera_instance.rotate(glm::radians(0.42f), glm::vec3(1.0f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera_instance.rotate(glm::radians(-0.42f), glm::vec3(1.0f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera_instance.rotate(glm::radians(0.42f), glm::vec3(0.0f, 1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera_instance.rotate(glm::radians(-0.42f), glm::vec3(0.0f, 1.0f, 0.0f));
}

// TODO: importer를 class화 하기
void	DoTheSceneProcessing(const aiScene  &pScene)
{
	std::cout << &pScene << std::endl;
}

bool	Importer(const std::string &pFile)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(pFile, 
	aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);

  // If the import failed, report it
	if (scene == nullptr) {
		std::cout << std::string(importer.GetErrorString()) << std::endl;
    return false;
	}

  // Now we can access the file's contents.
	DoTheSceneProcessing(*scene);

  // We're done. Everything will be cleaned up by the importer destructor
	return true;
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
	if (Importer("../asset/Dragon 2.5_fbx.fbx"))
	{
		std::cout << "SUCCESS" << std::endl;
	}
	else{
		std::cout << "FAILED 🥲" << std::endl;
	};


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
	glm::mat4 step = glm::mat4(1.0f);

	glm::mat4 projection;
	//FOR cam move
	// make sure to initialize matrix to identity matrix first
	float radius = 10.0f;
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
		step = glm::rotate(step, (float)glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		GLuint location = glGetUniformLocation(shader_program, "step");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(step));

		projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		GLuint projection_location = glGetUniformLocation(shader_program, "projection");
		glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

		// camera move
        glm::mat4 view = camera_instance.lookAt();
		GLuint view_location = glGetUniformLocation(shader_program, "view");
		glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
		// 그리기
		glUseProgram(shader_program);
		glBindVertexArray(buffer_instance.getVAO());
		glDrawElements(GL_TRIANGLES, buffer_instance.getIndices().size(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader_program);
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
