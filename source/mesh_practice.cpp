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
//void	DoTheSceneProcessing(const aiScene  &pScene)
//{
	
//	std::cout << &pScene << std::endl;
//}

const aiScene *Importer(const std::string &pFile)
{
	Assimp::Importer importer;

	const aiScene * scene = importer.ReadFile(pFile, 
	aiProcess_CalcTangentSpace       |
	aiProcess_Triangulate            |
	aiProcess_JoinIdenticalVertices  |
	aiProcess_SortByPType);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << std::string(importer.GetErrorString()) << std::endl;
		return nullptr;
	}
	// TODO: scene에 불러온값들 파싱하기.!
	// Now we can access the file's contents.
	//DoTheSceneProcessing(*scene);

  // We're done. Everything will be cleaned up by the importer destructor
	return scene;
}

int main_process()
{
    GLWindowWrapper window_instance(600, 800, "hi");

	GLFWwindow* window = window_instance.getWindow();


	const aiScene * scene = Importer(std::filesystem::path(ROOT_PATH) / "asset/model2_coin.fbx");
	if (scene)
	{
		std::cout << "SUCCESS" << std::endl;
	}
	else{
		std::cout << "FAILED 🥲" << std::endl;
		std::exit(1);
	};

	// Mesh part
	
	return(EXIT_SUCCESS);
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
		// glUseProgram(shader_program);
		//glBindVertexArray(buffer_instance.getVAO());
		//glDrawElements(GL_TRIANGLES, buffer_instance.getIndices().size(), GL_UNSIGNED_INT, nullptr);

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
