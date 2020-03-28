#include "engine_pch.h"
#include "worldGrid.h"
#include "Headers/systems/log.h"
#include "Headers/renderer/shaderDataType.h"
#include "Headers/renderer/vertexBufferLayout.h"
#include "glm/glm.hpp"

namespace ParticleDesigner
{
	WorldGrid::WorldGrid()
	{
		m_shader = std::shared_ptr<Engine::Renderer::Shader>(Engine::Renderer::Shader::create("assets/shaders/worldGrid.shader"));
		m_vertexArray = std::shared_ptr<Engine::Renderer::VertexArray>(Engine::Renderer::VertexArray::create());

		float halfSize = (m_numberOfSquares * m_squareSize) / 2.0f;

		for (int i = 0; i < m_numberOfSquares + 1; i++)
		{
			m_gridData.push_back(-halfSize + (m_squareSize * i));
			m_gridData.push_back(0.0f);
			m_gridData.push_back(halfSize);


			m_gridData.push_back(-halfSize + (m_squareSize * i));
			m_gridData.push_back(0.0f);
			m_gridData.push_back(halfSize - m_numberOfSquares * m_squareSize);
		}

		for (int i = 0; i < m_numberOfSquares + 1; i++)
		{
			m_gridData.push_back(-halfSize);
			m_gridData.push_back(0.0f);
			m_gridData.push_back(halfSize - (m_squareSize * i));


			m_gridData.push_back(-halfSize + m_numberOfSquares * m_squareSize);
			m_gridData.push_back(0.0f);
			m_gridData.push_back(halfSize - (m_squareSize * i));
		}

		Engine::Renderer::VertexBufferLayout layout = { Engine::Renderer::ShaderDataType::Float3 };
		m_vertexBuffer = std::shared_ptr<Engine::Renderer::VertexBuffer>(Engine::Renderer::VertexBuffer::create(&m_gridData[0], m_gridData.size() / 3, layout));
		m_vertexArray->setVertexBuffer(m_vertexBuffer);
		m_material = std::shared_ptr<Engine::Renderer::Material>(Engine::Renderer::Material::create(m_shader, m_vertexArray));
	}
	WorldGrid::~WorldGrid()
	{

	}
}