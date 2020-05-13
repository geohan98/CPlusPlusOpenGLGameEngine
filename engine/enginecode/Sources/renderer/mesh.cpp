#include "engine_pch.h"
#include "Headers/renderer/mesh.h"
#include "Headers/systems/log.h"
#include "Headers/renderer/shaderDataType.h"
#include "Headers/renderer/vertexBufferLayout.h"


namespace Engine
{
	Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::string _texFileName)
	{
		m_vertices = _vertices;
		m_indices = _indices;
		if (!_texFileName.empty())
		{
			m_Texture = std::shared_ptr<Renderer::Texture>(Renderer::Texture::createFromFile(_texFileName));
			m_textureslot = m_Texture->getSlot();
		}
		else
		{
			m_Texture = std::shared_ptr<Renderer::Texture>(Renderer::Texture::createFromFile("assets/textures/GridWhite.png"));
		}
		setupMesh();
	}
	Mesh::~Mesh()
	{
	}

	void Mesh::setupMesh()
	{
		m_VAO = std::shared_ptr<Renderer::VertexArray>(Renderer::VertexArray::create());
		Renderer::VertexBufferLayout EBO = { Renderer::ShaderDataType::Float3,Renderer::ShaderDataType::Float3, Renderer::ShaderDataType::Float2, Renderer::ShaderDataType::Float3,Renderer::ShaderDataType::Float3 };
		//m_VBO = std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(&m_vertices[0].position.x, m_vertices.size(), EBO));
		std::vector<float> tempfloats;
		tempfloats.resize(14 * m_vertices.size());
		int i = 0;
		for (auto v : m_vertices)
		{
			tempfloats[i] = v.position.x; i++;
			tempfloats[i] = v.position.y; i++;
			tempfloats[i] = v.position.z; i++;
			tempfloats[i] = v.normal.x; i++;
			tempfloats[i] = v.normal.y; i++;
			tempfloats[i] = v.normal.z; i++;
			tempfloats[i] = v.texCoords.x; i++;
			tempfloats[i] = v.texCoords.y; i++;
			tempfloats[i] = v.tangent.x; i++;
			tempfloats[i] = v.tangent.y; i++;
			tempfloats[i] = v.tangent.z; i++;
			tempfloats[i] = v.bitangent.x; i++;
			tempfloats[i] = v.bitangent.y; i++;
			tempfloats[i] = v.bitangent.z; i++;
		}
		m_VBO = std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(tempfloats.data(), tempfloats.size() * sizeof(float) / EBO.getStride(), EBO));
		m_IBO = std::shared_ptr<Renderer::IndexBuffer>(Renderer::IndexBuffer::create(&m_indices[0], m_indices.size()));
		m_VAO->setVertexBuffer(m_VBO);
		m_VAO->setIndexBuffer(m_IBO);
		m_shader = std::shared_ptr<Renderer::Shader>(Renderer::Shader::create("assets/shaders/defaultShader.shader"));
		m_MAT = std::shared_ptr<Renderer::Material>(Renderer::Material::create(m_shader, m_VAO));
		if (m_Texture != nullptr) m_MAT->setDataElement("u_texData", (void*)&m_textureslot);
	}
}
