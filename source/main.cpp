#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

string file_loader(const filesystem::path& file_name)
{
	ifstream ifs(file_name);
	if (!ifs.is_open())
	{
		throw string("Error: Failed to open file: ") + file_name.string();
	}
	stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();
	return ss.str();
}


class Shader {
    private:
        GLuint m_shader;
        Shader(){ };
    public:
        Shader(const filesystem::path & shader_path, GLenum shader_kind)
        {
			m_shader = glCreateShader(shader_kind); // 셰이더 오브젝트 생성
			string shader_source = file_loader(shader_path);
			const char* shader_source_ptr = shader_source.data();
			glShaderSource(m_shader, 1, &shader_source_ptr, nullptr); // 셰이더 소스파일 로드
			glCompileShader(m_shader); // 셰이더 컴파일
			int success;
			glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); // 잘 됐는지 확인
			if (!success)
			{
				char log[512];
				glGetShaderInfoLog(m_shader, 512, nullptr, log); // 로그 확인
				throw ShaderException(std::string("Error: Failed to compile vertex shader:\n") + log);
			}
		}
        ~Shader()
        {
            glDeleteShader(this->m_shader);
        }

        class ShaderException: public std::exception
	    {
            private:
		        std::string errMessage;

    		public:
			ShaderException(const std::string& errMessage)
			{
				this->errMessage = errMessage;	
			}
            const char* what() const _NOEXCEPT
            {
                return (this->errMessage).c_str();
            }
	    };

        GLuint getShader()
        {
            return this->m_shader;
        }
};

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
		/*glDelete~~*/
		glfwTerminate();
	}

    void UseThisWindow(void)
    {
    	glfwMakeContextCurrent(this->window);
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

	GLFWwindow* getWindow(){
		return window;
	}
};


class ShaderProgram
{
    private:
		GLuint vertex_shader;
		GLuint fragment_shader;
       	GLuint shader_program; 
        ShaderProgram() {};
    public:
        ShaderProgram(GLuint vertex_shader_data, GLuint fragment_shader_data)
        {
			this->vertex_shader = vertex_shader_data;
			this->fragment_shader = fragment_shader_data;
            this->shader_program = glCreateProgram();
            glAttachShader(this->shader_program, this->vertex_shader); 
            glAttachShader(this->shader_program, this->fragment_shader);
            glLinkProgram(this->shader_program);
            int success;
            glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
            if (!success)
            {
                char log[512];
                glGetProgramInfoLog(shader_program, 512, nullptr, log);
                throw ShaderProgramException(std::string("ERROR: Failed to link shader program:\n") + log); 
            }
        }
        ~ShaderProgram()
        {
            glDeleteProgram(this->shader_program);
        }

        GLuint getShaderProgram()
        {
            return this->shader_program;
        }

        class ShaderProgramException: public std::exception
        {
            private:
                std::string m_errMessage;

            public:
                ShaderProgramException(const std::string &errMessage)
                {
                    this->m_errMessage = errMessage;	
                }

                const char *what() const _NOEXCEPT
                {
                    return (this->m_errMessage).c_str();
                }
	    };
};



int main_process()
{
    GLWindowWrapper window_instance;
    Shader          vertex_shader(filesystem::path(ROOT_PATH) / "source/basic.vert", GL_VERTEX_SHADER);
    Shader          fragment_shader(filesystem::path(ROOT_PATH) / "source/basic.frag", GL_FRAGMENT_SHADER);
    GLuint          vertex_shader_data = vertex_shader.getShader();
    GLuint          fragment_shader_data = fragment_shader.getShader();
    ShaderProgram   shaderprogram_instance(vertex_shader_data, fragment_shader_data);
    
	GLFWwindow* window = window_instance.getWindow();
	GLuint shader_program = shaderprogram_instance.getShaderProgram();


	// 출력할 데이터
	vector<Vertex> vertices = {
		{{ 0.5f,  0.5f,  0.0f}, {0.5f, 1.0f, 1.0f}},
		{{ 0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
		{{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
	};

	vector<GLuint> indices = {
		0, 1, 2,
		1, 2, 3,
	};

	// 버퍼
	GLuint vertex_array_obj;
	GLuint vertex_buffer_obj;
	GLuint element_buffer_obj;

	glGenVertexArrays(1, &vertex_array_obj);
	glGenBuffers(1, &vertex_buffer_obj);
	glGenBuffers(1, &element_buffer_obj);
	
	glBindVertexArray(vertex_array_obj);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_obj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);


	// 렌더링 루프
	while (!glfwWindowShouldClose(window))
	{
		key_manager(window);
		// 렌더링
		// 버퍼 초기화
		// 넘치면 1, 음수면 0으로 해줌
		glClearColor(3232321.0f, -43141341.0f, -11241251325.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 그리기
		glUseProgram(shader_program);
		glBindVertexArray(vertex_array_obj);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vertex_array_obj);
	glDeleteBuffers(1, &vertex_buffer_obj);
	glDeleteBuffers(1, &element_buffer_obj);
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
