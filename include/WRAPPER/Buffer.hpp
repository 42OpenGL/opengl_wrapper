#pragma once

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

class Buffer
	{
		private:
			std::vector<Vertex> _vertices = {
							{{ 0.5f,  0.5f,  0.0f}, {0.5f, 1.0f, 1.0f}},
							{{ 0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
							{{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
							{{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
						};
			std::vector<GLuint> _indices =  {
							0, 1, 2,
							1, 2, 3,
						};
			GLuint _vertex_array_obj;
			GLuint _vertex_buffer_obj;
			GLuint _element_buffer_obj;
		public:
			Buffer() : _vertex_array_obj(0), _vertex_buffer_obj(0), _element_buffer_obj(0)
			{
				// TODO: 생성자 초기화
				glGenVertexArrays(1, &_vertex_array_obj);
				glGenBuffers(1, &_vertex_buffer_obj);
				glGenBuffers(1, &_element_buffer_obj);
				
				glBindVertexArray(_vertex_array_obj);
				glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_obj);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer_obj);
				
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
				glEnableVertexAttribArray(1);

				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->_vertices.size(), this->_vertices.data(), GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->_indices.size(), this->_indices.data(), GL_STATIC_DRAW);
			}
			~Buffer()
			{
				// TODO: 동적할당, 동적해제할 떄 가드하기!!
				if (!_vertex_array_obj)
					glDeleteVertexArrays(1, &_vertex_array_obj);
				if (!_vertex_buffer_obj)
					glDeleteBuffers(1, &_vertex_buffer_obj);
				if (!_element_buffer_obj)
					glDeleteBuffers(1, &_element_buffer_obj);
			}

			// TODO: 레퍼런스로 받기
			void setVertices(const std::vector<Vertex> &new_vertices)
			{
				this->_vertices = new_vertices;
				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->_vertices.size(), this->_vertices.data(), GL_STATIC_DRAW);
			}

			void setIndices(const std::vector<GLuint> &new_indices)
			{
				this->_indices = new_indices;
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->_indices.size(), this->_indices.data(), GL_STATIC_DRAW);
			}
			
			GLuint getVAO()
			{
				return this->_vertex_array_obj;
			}

			std::vector<GLuint> getIndices()
			{
				return this->_indices;
			}
	};