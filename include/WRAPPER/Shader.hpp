#progrma once

std::string file_loader(const std::filesystem::path& file_name)
{
	std::ifstream ifs(file_name);
	if (!ifs.is_open())
	{
		throw std::string("Error: Failed to open file: ") + file_name.string();
	}
	std::stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();
	return ss.str();
}

class Shader {
    private:
        GLuint m_shader;
        Shader(){ };
    public:
        Shader(const std::filesystem::path & shader_path, GLenum shader_kind)
        {
			m_shader = glCreateShader(shader_kind); // 셰이더 오브젝트 생성
			std::string shader_source = file_loader(shader_path);
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

        GLuint getShader()
        {
            return this->m_shader;
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
};