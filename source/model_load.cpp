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


#include "../include/model/Model.hpp"

int lastX = 0, lastY = 0;
bool firstMouse = true;
bool mouse_clicked = false;
Camera	camera_instance(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

void mouse_move_callback(GLFWwindow * window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);

void key_manager(GLFWwindow *window);

int main_process()
{
    GLWindowWrapper window_instance(800, 800, "hi");
	GLFWwindow* window = window_instance.getWindow();

    Shader          vertex_shader_instance(std::filesystem::path(ROOT_PATH) / "source/assimp_shader.vert", GL_VERTEX_SHADER);
    Shader          fragment_shader_instance(std::filesystem::path(ROOT_PATH) / "source/assimp_shader.frag", GL_FRAGMENT_SHADER);
    GLuint          vertex_shader_data = vertex_shader_instance.getShader();
    GLuint          fragment_shader_data = fragment_shader_instance.getShader();
	std::vector<GLuint> shader_vector = {vertex_shader_data, fragment_shader_data};
	ShaderProgram shader_program_instance(shader_vector);
	GLuint shader_program_id = shader_program_instance.getShaderProgram();
	

	//Model	model_instance(std::filesystem::path(ROOT_PATH) / "asset/new_dragon/smaug.obj");
	Model	model_instance(std::filesystem::path(ROOT_PATH) / "asset/backpack/backpack.obj");
	//Model	model_instance(std::filesystem::path(ROOT_PATH) / "asset/Survival_BackPack_2/Survival_BackPack_2.fbx");
	//Model	model_instance(std::filesystem::path(ROOT_PATH) / "asset/coin/model2_coin.fbx");
	
	glEnable(GL_DEPTH_TEST);

	glm::mat4 projection;
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);
	while (!glfwWindowShouldClose(window))
	{
		key_manager(window);
		// 렌더링
		// 버퍼 초기화
		// 넘치면 1, 음수면 0으로 해줌
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		GLuint projection_location = glGetUniformLocation(shader_program_id, "projection");
		glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

		// camera move
        glm::mat4 view = camera_instance.lookAt();
		GLuint view_location = glGetUniformLocation(shader_program_id, "view");
		glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
		
		// 그리기
		glUseProgram(shader_program_id);
		model_instance.Draw(shader_program_instance);		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader_program_id);
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

void key_manager(GLFWwindow *window)
{
	//float step = 0.042;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_instance.go_foward();
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_instance.go_backward();
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_instance.go_left();
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_instance.go_right();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera_instance.go_down();
		else
			camera_instance.go_up();
	}
}

void mouse_move_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (mouse_clicked == false)
		return ;

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	std::cout << "(" << xpos << "," << ypos << ")" << std::endl;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
		return ;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.42f; // change this value to your liking

	camera_instance.rotate(glm::radians(sensitivity), glm::normalize(glm::vec3(-yoffset, xoffset, 0.0f)));
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		mouse_clicked = true;
	else
		mouse_clicked = false;
}