#include <glad/glad.h>
#include <exception>
#include <iostream>

/*
- 멤버변수
	vertices
	indices

*/
class GLWindowWrapper {

private:
	GLFWwindow*	window;

public :
	GLWindowWrapper()
	{
	 	if (!glfwInit())
		{
			throw GLWindowWrapperException("failed to initialize GLFW");
		}
		glfwWindowHint(GLFW_SAMPLES, 4); // 안티엘리어싱 x4
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 최대버전: 그냥 glfw 버전
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 최소버전: 그냥 glfw 버전
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 프로파일 버전: 코어
		#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif

		GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", nullptr, nullptr);
		if (window == NULL)
		{
			throw GLWindowWrapperException("Error: Failed to create GLFW window");
		}
	}
	~GLWindowWrapper()
	{
		/*glDelete~~*/
		glfwTerminate();
	}

	class GLWindowWrapperException: public std::exception
	{
		std:string errMessage;

		public:
			GLWindowWrapperException(const std:string& errMessage)
			{
				this->errMessage = errMessage;	
			}

		const char* what() const{
			return this->errMessage;
		};
	}

	GLFWwindow* getWindow(){
		return window;
	}
}

int main()
{
	try {
		GLWindowWrapper w;
		GLFWwindow* window;

		window = w.getWindow();
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;	
	}
}
