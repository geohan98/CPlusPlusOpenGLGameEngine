#pragma once
#include "Headers/renderer/material.h"
#include "Headers/renderer/vertexArray.h"
#include "Headers/renderer/vertexBuffer.h"
#include "Headers/renderer/shader.h"



namespace ParticleEditor
{
	class WorldGrid
	{
	private:
		float m_squareDivisions = 10; //Minimum is 1
		int m_numberOfSquares = 10;
	public:
		WorldGrid();
		~WorldGrid();
		std::shared_ptr<Engine::Renderer::Material> m_material;
		std::shared_ptr<Engine::Renderer::VertexArray> m_vertexArray;
		std::shared_ptr<Engine::Renderer::VertexBuffer> m_vertexBuffer;
		std::shared_ptr<Engine::Renderer::Shader> m_shader;
		std::vector<float> m_gridData;

		inline std::shared_ptr<Engine::Renderer::Material>& getMaterial() { return m_material; }
	};
}