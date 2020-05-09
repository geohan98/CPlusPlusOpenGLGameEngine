#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Headers/renderer/material.h"
#include "Headers/renderer/vertexArray.h"
#include "Headers/renderer/vertexBuffer.h"
#include "Headers/renderer/indexBuffer.h"
#include "Headers/renderer/material.h"
#include "Headers/renderer/shader.h"
#include "Headers/renderer/texture.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

namespace Engine
{
	class Mesh
	{
	private:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::shared_ptr<Renderer::Material> m_MAT;
		std::shared_ptr<Renderer::VertexArray> m_VAO;
		std::shared_ptr<Renderer::VertexBuffer> m_VBO;
		std::shared_ptr<Renderer::IndexBuffer> m_IBO;
		std::shared_ptr<Renderer::Shader> m_shader;
		std::shared_ptr<Renderer::Texture> m_Texture;  //Creating a variable for implementing Texture to object
		int m_textureslot; // Creating a slot to insert a texture
		void setupMesh(); // Void function to setup the object mesh
	public:
		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::string _texFileName);
		~Mesh(); //Mesh constructor to inclues the vertex size, indices size, and filename location
		inline std::shared_ptr<Renderer::Material> getMaterial() { return m_MAT; } // Get the material needed for the object
	};
}