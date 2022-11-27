#pragma once
#include <exception>
#include <vector>

class ShaderProgram
{
    private:
		std::vector<GLuint>  _shaders;
       	GLuint               _shader_program; 
    public:
        ShaderProgram()
        {
            this->_shader_program = glCreateProgram();
        }
        explicit ShaderProgram(const std::vector<GLuint> & shaders) 
        {
            this->_shader_program = glCreateProgram();
            std::vector<GLuint>::const_iterator it = shaders.begin();
            for (; it < shaders.end() ; it++)
                putShader(*it);
        }
        ~ShaderProgram()
        {
            glDeleteProgram(this->_shader_program);
        }

        void putShader(GLuint shader_data)
        {
            glAttachShader(this->_shader_program, shader_data);
        }

        GLuint getShaderProgram() const
        {
            int success;
            glLinkProgram(this->_shader_program);
            glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
            if (!success)
            {
                char log[512];
                glGetProgramInfoLog(_shader_program, 512, nullptr, log);
                throw std::runtime_error(std::string("ERROR: Failed to link shader program:\n") + log); 
            }
            return this->_shader_program;
        }
};