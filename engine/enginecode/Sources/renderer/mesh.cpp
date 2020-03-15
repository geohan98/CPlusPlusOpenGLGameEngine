#include "engine_pch.h"
#include "Headers/renderer/mesh.h"
#include "Headers/systems/log.h"
#include "Headers/renderer/shaderDataType.h"
#include "Headers/renderer/vertexBufferLayout.h"


namespace Engine
{
	Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices)
	{
		m_vertices = _vertices;
		m_indices = _indices;
		setupMesh();
	}
	Mesh::~Mesh()
	{
	}

	void Mesh::setupMesh()
	{
		m_VAO = std::shared_ptr<Renderer::VertexArray>(Renderer::VertexArray::create());
		Renderer::VertexBufferLayout EBO = { Renderer::ShaderDataType::Float3,Renderer::ShaderDataType::Float3, Renderer::ShaderDataType::Float2, Renderer::ShaderDataType::Float3,Renderer::ShaderDataType::Float3 };
		m_VBO = std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(&m_vertices[0].position.x, m_vertices.size(), EBO));
		m_IBO = std::shared_ptr<Renderer::IndexBuffer>(Renderer::IndexBuffer::create(&m_indices[0], m_indices.size()));
		m_VAO->setVertexBuffer(m_VBO);
		m_VAO->setIndexBuffer(m_IBO);
		m_shader = std::shared_ptr<Renderer::Shader>(Renderer::Shader::create("assets/shaders/Debug/debug.shader"));
		m_MAT = std::shared_ptr<Renderer::Material>(Renderer::Material::create(m_shader, m_VAO));
	}
}
