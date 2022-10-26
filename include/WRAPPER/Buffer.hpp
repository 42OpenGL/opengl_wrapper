#pragma once

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

class Buffer
	{
		private:
		// TODO: inline 으로 초기화
		// TODO: buffer에도 여러개 받을 수 있게 확장하기
		// TODO: vertices가 다양함. -> 여러 vertices를 대응할 수 있도록
			std::vector<Vertex> vertices = {
							{{ 0.5f,  0.5f,  0.0f}, {0.5f, 1.0f, 1.0f}},
							{{ 0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
							{{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
							{{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 0.0f}},
						};
			std::vector<GLuint> indices =  {
							0, 1, 2,
							1, 2, 3,
						};
			GLuint vertex_array_obj;
			GLuint vertex_buffer_obj;
			GLuint element_buffer_obj;
		public:
			Buffer(): vertex_array_obj(0), vertex_buffer_obj(0), element_buffer_obj(0)
			{
				// TODO: 생성자 초기화
				glGenVertexArrays(1, &vertex_array_obj);
				glGenBuffers(1, &vertex_buffer_obj);
				glGenBuffers(1, &element_buffer_obj);
				
				glBindVertexArray(vertex_array_obj);
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_obj);
				
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
				glEnableVertexAttribArray(1);

				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);
			}
			~Buffer()
			{
				// TODO: 동적할당, 동적해제할 떄 가드하기!!
				if (!vertex_array_obj)
					glDeleteVertexArrays(1, &vertex_array_obj);
				if (!vertex_buffer_obj)
					glDeleteBuffers(1, &vertex_buffer_obj);
				if (!element_buffer_obj)
					glDeleteBuffers(1, &element_buffer_obj);
			}

			// TODO: 레퍼런스로 받기
			void setVertices(const std::vector<Vertex> &new_vertices)
			{
				std::cout << (long)&new_vertices[0] << std::endl;
				// swap -> 보류. 
				this->vertices = new_vertices;
				std::cout << (long)&(this->vertices[0]) << std::endl;
				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
			}

			void setIndices(const std::vector<GLuint> &new_indices)
			{
				this->indices = new_indices;
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);
			}
			
			GLuint getVAO()
			{
				return this->vertex_array_obj;
			}

			std::vector<GLuint> getIndices()
			{
				return this->indices;
			}
	};