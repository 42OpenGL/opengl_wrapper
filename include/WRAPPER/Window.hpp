#pragma once

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

			// TODO: 창크기, 창이름
			this->window = glfwCreateWindow(800, 600, "Hello Window", nullptr, nullptr);
			if (this->window == NULL)
			{
				throw GLWindowWrapperException("Error: Failed to create GLFW window");
			}
			this->UseThisWindow();
			// OpenGL 함수 포인터와 실제 함수를 매핑
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				throw GLWindowWrapperException("Error: Failed to initialize GLAD");
			}
		}
		~GLWindowWrapper()
		{
			glfwTerminate();
		}

		void UseThisWindow(void)
		{
			glfwMakeContextCurrent(this->window);
		}
		
		GLFWwindow* getWindow(){
			return window;
		}

		class GLWindowWrapperException: public std::exception
		{
			private:
				std::string m_errMessage;

			public:
				GLWindowWrapperException(const std::string &errMessage)
				{
					this->m_errMessage = errMessage;	
				}

				const char *what() const _NOEXCEPT
				{
					return (this->m_errMessage).c_str();
				}
		};
};