#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/WRAPPER/Shader.hpp"
#include "../include/WRAPPER/ShaderProgram.hpp"
#include "../include/WRAPPER/Window.hpp"
#include "../include/WRAPPER/Buffer.hpp"
#include "../include/WRAPPER/Camera.hpp"

// 3d model loading
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../include/model/Model.hpp"

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
 
int main_process()
{
    GLWindowWrapper window_instance(800, 600, "backpack");
	GLFWwindow* window = window_instance.getWindow();
	Shader	vertex_shader_instance(std::filesystem::path(ROOT_PATH)/"source/assimp_shader.vert", GL_VERTEX_SHADER);
	Shader	fragment_shader_instance(std::filesystem::path(ROOT_PATH)/"source/assimp_shader.frag", GL_FRAGMENT_SHADER);
	std::vector<GLuint> shader_vector = {vertex_shader_instance.getShader(), fragment_shader_instance.getShader()};
	ShaderProgram	shader_program_instance(shader_vector);
	GLuint			shader_program = shader_program_instance.getShaderProgram();

	Model	model_instance(std::filesystem::path(ROOT_PATH) / "asset/Survival_BackPack_2/Survival_BackPack_2.fbx");
		
	// 렌더링 루프
	glm::mat4 projection;
	while (!glfwWindowShouldClose(window))
	{
		key_manager(window);
		// 렌더링
		// 버퍼 초기화
		// 넘치면 1, 음수면 0으로 해줌
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		GLuint projection_location = glGetUniformLocation(shader_program, "projection");
		glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

		// camera move
        glm::mat4 view = camera_instance.lookAt();
		GLuint view_location = glGetUniformLocation(shader_program, "view");
		glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		GLuint model_location = glGetUniformLocation(shader_program, "model");
		glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));	
		
		glUseProgram(shader_program);
		model_instance.Draw(shader_program_instance);		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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
