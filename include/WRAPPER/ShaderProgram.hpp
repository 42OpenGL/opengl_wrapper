#progrma once

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