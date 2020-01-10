#include "engine_pch.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_material.h"

namespace Engine
{
	OpenGL_Material::OpenGL_Material(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		m_shader = Shader;
		m_geomertry = vertexArray;
	}

	void OpenGL_Material::init(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		m_shader = Shader;
		m_geomertry = vertexArray;
	}

	void OpenGL_Material::setShader(const std::shared_ptr<Shader>& shader)
	{
		m_shader = shader;
	}

	void OpenGL_Material::setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry)
	{
		m_geomertry = std::get < std::shared_ptr<VertexArray>>(geometry);
	}

	void OpenGL_Material::setDataBlock(const std::map<std::string, void*>& data)
	{
		m_data = data;
	}

	void OpenGL_Material::setDataElement(const std::string& dataName, void* data)
	{
		m_data[dataName] = data;
	}

	void OpenGL_Material::setVertexData(float* vertices, unsigned int size, unsigned int offset)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("FUNCTION NOT IMPLIMENTED, setVertexData(float* vertices, unsigned int size, unsigned int offset)");
#endif // NG_DEBUG
	}

}