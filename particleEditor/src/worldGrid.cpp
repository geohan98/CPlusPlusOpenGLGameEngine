#include "engine_pch.h"
#include "worldGrid.h"
#include "Headers/systems/log.h"
#include "Headers/renderer/shaderDataType.h"
#include "Headers/renderer/vertexBufferLayout.h"
#include "glm/glm.hpp"
#include <math.h>

namespace ParticleEditor
{
	WorldGrid::WorldGrid()
	{
		m_shader = std::shared_ptr<Engine::Renderer::Shader>(Engine::Renderer::Shader::create("assets/shaders/worldGrid.shader"));
		m_vertexArray = std::shared_ptr<Engine::Renderer::VertexArray>(Engine::Renderer::VertexArray::create());

		float halfSize = m_numberOfSquares / 2.0f;
		int numLines = (m_numberOfSquares + 1) + (m_squareDivisions - 1) * m_numberOfSquares;
		float lineGap = m_numberOfSquares / (numLines - 1.0f);
		Engine::LOG_CORE_INFO("NUM OF LINES{0}", lineGap);

		for (int i = 0; i < numLines; i++)
		{
			//Start Point
			m_gridData.push_back(-halfSize + i * lineGap);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(halfSize);//Z

			if (i == 0 || i == numLines - 1)
			{
				m_gridData.push_back(1.0f);//R
				m_gridData.push_back(1.0f);//G
				m_gridData.push_back(0.0f);//B
				m_gridData.push_back(1.0f);//A
			}
			else
			{
				if (std::fmodf(i, m_squareDivisions) == 0)
				{
					m_gridData.push_back(1.0f);//R
					m_gridData.push_back(1.0f);//G
					m_gridData.push_back(1.0f);//B
					m_gridData.push_back(1.0f);//A
				}
				else
				{
					m_gridData.push_back(0.2f);//R
					m_gridData.push_back(0.2f);//G
					m_gridData.push_back(0.2f);//B
					m_gridData.push_back(0.2f);//A
				}
			}

			//End Point
			m_gridData.push_back(-halfSize + i * lineGap);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(halfSize - m_numberOfSquares);//Z

			if (i == 0 || i == numLines - 1)
			{
				m_gridData.push_back(1.0f);//R
				m_gridData.push_back(1.0f);//G
				m_gridData.push_back(0.0f);//B
				m_gridData.push_back(1.0f);//A
			}
			else
			{
				if (std::fmodf(i, m_squareDivisions) == 0)
				{
					m_gridData.push_back(1.0f);//R
					m_gridData.push_back(1.0f);//G
					m_gridData.push_back(1.0f);//B
					m_gridData.push_back(1.0f);//A
				}
				else
				{
					m_gridData.push_back(0.2f);//R
					m_gridData.push_back(0.2f);//G
					m_gridData.push_back(0.2f);//B
					m_gridData.push_back(0.2f);//A
				}
			}
		}

		for (int i = 0; i < numLines; i++)
		{
			//Start Point
			m_gridData.push_back(halfSize);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(-halfSize + i * lineGap);//Z

			if (i == 0 || i == numLines - 1)
			{
				m_gridData.push_back(1.0f);//R
				m_gridData.push_back(1.0f);//G
				m_gridData.push_back(0.0f);//B
				m_gridData.push_back(1.0f);//A
			}
			else
			{
				if (std::fmodf(i, m_squareDivisions) == 0)
				{
					m_gridData.push_back(1.0f);//R
					m_gridData.push_back(1.0f);//G
					m_gridData.push_back(1.0f);//B
					m_gridData.push_back(1.0f);//A
				}
				else
				{
					m_gridData.push_back(0.2f);//R
					m_gridData.push_back(0.2f);//G
					m_gridData.push_back(0.2f);//B
					m_gridData.push_back(0.2f);//A
				}
			}

			//End Point

			m_gridData.push_back(halfSize - m_numberOfSquares);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(-halfSize + i * lineGap);//Z

			if (i == 0 || i == numLines - 1)
			{
				m_gridData.push_back(1.0f);//R
				m_gridData.push_back(1.0f);//G
				m_gridData.push_back(0.0f);//B
				m_gridData.push_back(1.0f);//A
			}
			else
			{
				if (std::fmodf(i, m_squareDivisions) == 0)
				{
					m_gridData.push_back(1.0f);//R
					m_gridData.push_back(1.0f);//G
					m_gridData.push_back(1.0f);//B
					m_gridData.push_back(1.0f);//A
				}
				else
				{
					m_gridData.push_back(0.2f);//R
					m_gridData.push_back(0.2f);//G
					m_gridData.push_back(0.2f);//B
					m_gridData.push_back(0.2f);//A
				}
			}

			//X Line
			//Start
			m_gridData.push_back(0.0f);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(0.0f);//Z

			m_gridData.push_back(1.0f);//R
			m_gridData.push_back(0.0f);//G
			m_gridData.push_back(0.0f);//B
			m_gridData.push_back(1.0f);//A

			//End
			m_gridData.push_back(halfSize);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(0.0f);//Z

			m_gridData.push_back(1.0f);//R
			m_gridData.push_back(0.0f);//G
			m_gridData.push_back(0.0f);//B
			m_gridData.push_back(1.0f);//A

			//Y Line
			//Start
			m_gridData.push_back(0.0f);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(0.0f);//Z

			m_gridData.push_back(0.0f);//R
			m_gridData.push_back(1.0f);//G
			m_gridData.push_back(0.0f);//B
			m_gridData.push_back(1.0f);//A

			//End
			m_gridData.push_back(0.0f);//X
			m_gridData.push_back(halfSize);//Y
			m_gridData.push_back(0.0f);//Z

			m_gridData.push_back(0.0f);//R
			m_gridData.push_back(1.0f);//G
			m_gridData.push_back(0.0f);//B
			m_gridData.push_back(1.0f);//A

			//Z Line
			//Start
			m_gridData.push_back(0.0f);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(0.0f);//Z

			m_gridData.push_back(0.0f);//R
			m_gridData.push_back(0.0f);//G
			m_gridData.push_back(1.0f);//B
			m_gridData.push_back(1.0f);//A

			//End
			m_gridData.push_back(0.0f);//X
			m_gridData.push_back(0.0f);//Y
			m_gridData.push_back(halfSize);//Z

			m_gridData.push_back(0.0f);//R
			m_gridData.push_back(0.0f);//G
			m_gridData.push_back(1.0f);//B
			m_gridData.push_back(1.0f);//A
		}



		Engine::Renderer::VertexBufferLayout layout = { Engine::Renderer::ShaderDataType::Float3,Engine::Renderer::ShaderDataType::Float4 };
		m_vertexBuffer = std::shared_ptr<Engine::Renderer::VertexBuffer>(Engine::Renderer::VertexBuffer::create(&m_gridData[0], m_gridData.size() / 7, layout));
		m_vertexArray->setVertexBuffer(m_vertexBuffer);
		m_material = std::shared_ptr<Engine::Renderer::Material>(Engine::Renderer::Material::create(m_shader, m_vertexArray));
	}
	WorldGrid::~WorldGrid()
	{

	}
}