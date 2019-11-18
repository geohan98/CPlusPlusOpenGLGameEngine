#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_vertexArray.h"
#include "glad/glad.h"
#include "systems/log.h"

namespace Engine
{
	OpenGL_VertexArray::OpenGL_VertexArray()
	{
		glGenVertexArrays(1, &m_rendererID);
	}
	void OpenGL_VertexArray::bind()
	{
		glBindVertexArray(m_rendererID);
	}
	void OpenGL_VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
	void OpenGL_VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
	}
	void OpenGL_VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer)
	{
	}
	std::shared_ptr<VertexBuffer> OpenGL_VertexArray::getVertexBuffer() const
	{
		return std::shared_ptr<VertexBuffer>();
	}
	std::shared_ptr<IndexBuffer> OpenGL_VertexArray::getIndexBuffer() const
	{
		return std::shared_ptr<IndexBuffer>();
	}
	unsigned int OpenGL_VertexArray::getDrawCount() const
	{
		return 0;
	}
}