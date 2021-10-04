#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <memory>
#include<vector>

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh(std::vector<Texture>texture,
		std::vector<Vertex>vertex,
		std::vector< GLuint > indices);

	GLvoid draw(Shader& shader);

private:
	std::vector <Texture> m_texture;
	std::vector <Vertex> m_vertices;
	std::vector < GLuint > m_indices;

	GLuint VBO, EBO, VAO;

	GLvoid SetUp();
};
#endif