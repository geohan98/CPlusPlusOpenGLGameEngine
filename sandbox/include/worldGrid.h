#pragma once
#include "Headers/renderer/material.h"
#include "Headers/renderer/vertexArray.h"
#include "Headers/renderer/vertexBuffer.h"
#include "Headers/renderer/shader.h"

class WorldGrid
{
private:
	float m_squareDivisions = 10; ///< How many times will a square be subdivided
	int m_numberOfSquares = 10; ///< How many squares willl be along a side of the grid
public:
	WorldGrid(); ///< Constructor
	~WorldGrid(); ///< Destructor
	std::shared_ptr<Engine::Renderer::Material> m_material; ///< Grid Material
	std::shared_ptr<Engine::Renderer::VertexArray> m_vertexArray; ///< Grid VAO
	std::shared_ptr<Engine::Renderer::VertexBuffer> m_vertexBuffer; ///< Grid VBO
	std::shared_ptr<Engine::Renderer::Shader> m_shader; ///< Grid Shader
	std::vector<float> m_gridData; ///< Vertex Data

	inline std::shared_ptr<Engine::Renderer::Material>& getMaterial() { return m_material; } ///< Get Grid Material
};
