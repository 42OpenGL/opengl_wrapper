#pragma once
#include <exception>

class GLWindowWrapper {
	private:
		int	_window_width;
		int _window_height;
		std::string	_window_name;
		GLFWwindow*	_pwindow;

	public :
		GLWindowWrapper(int width = 800, int height = 600, const std::string & name = "Hello world")
		: _window_width(width), _window_height(height), _window_name(name)
		{
			if (!glfwInit())
			{
				throw std::runtime_error("failed to initialize GLFW");
			}
			glfwWindowHint(GLFW_SAMPLES, 4); // 안티엘리어싱 x4
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 최대버전: 그냥 glfw 버전
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 최소버전: 그냥 glfw 버전
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 프로파일 버전: 코어
			#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			#endif

			// TODO: 창크기, 창이름
			this->_pwindow = glfwCreateWindow(_window_width, _window_height, _window_name.c_str(), nullptr, nullptr);
			if (this->_pwindow == NULL)
			{
				throw std::runtime_error("Error: Failed to create GLFW window");
			}
			this->UseThisWindow();
			// OpenGL 함수 포인터와 실제 함수를 매핑
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				throw std::runtime_error("Error: Failed to initialize GLAD");
			}
		}
		~GLWindowWrapper()
		{
			glfwTerminate();
		}

		void UseThisWindow(void)
		{
			glfwMakeContextCurrent(this->_pwindow);
		}
		
		GLFWwindow* getWindow(){
			return _pwindow;
		}
};