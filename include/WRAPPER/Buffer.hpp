#pragma once

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

class Buffer
	{
		private:
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
			Buffer()
			{
				glGenVertexArrays(1, &vertex_array_obj);
				glGenBuffers(1, &vertex_buffer_obj);
				glGenBuffers(1, &element_buffer_obj);
				
				glBindVertexArray(vertex_array_obj);
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_obj);
				
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);
			}
			~Buffer()
			{
				glDeleteVertexArrays(1, &vertex_array_obj);
				glDeleteBuffers(1, &vertex_buffer_obj);
				glDeleteBuffers(1, &element_buffer_obj);
			}

			void setVertices(std::vector<Vertex> new_vertices)
			{
				this->vertices = new_vertices;
				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
			}

			void setIndices(std::vector<GLuint> new_indices)
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