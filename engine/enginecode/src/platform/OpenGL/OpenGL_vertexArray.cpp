#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_vertexArray.h"
#include "glad/glad.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_vertexBuffer.h"
#include "include/platform/OpenGL/OpenGL_indexBuffer.h"

namespace Engine
{
	OpenGL_VertexArray::OpenGL_VertexArray()
	{
		glGenVertexArrays(1, &m_rendererID);
		glBindVertexArray(m_rendererID);
	}
	void OpenGL_VertexArray::bind()
	{
		glBindVertexArray(m_rendererID);
		m_indexBuffer->bind();
		m_vertexBuffer->bind();
	}
	void OpenGL_VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
	void OpenGL_VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_rendererID);
		vertexBuffer->bind();

		const auto& layout = vertexBuffer->getLayout();

		for (unsigned i = 0; i < layout.GetElements().size(); i++)
		{
			//LOG_CORE_INFO("Added Element");
			const auto& element = layout.GetElements()[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, ShaderDataTypeComponentCount(element.m_dataType), ShaderDataTypeToOpenGL(element.m_dataType), element.m_normalized, layout.getStride(), (const void*)element.m_offset);
		}

		m_vertexBuffer = vertexBuffer;
	}
	void OpenGL_VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_rendererID);
		indexBuffer->bind();
		m_indexBuffer = indexBuffer;
	}
	std::shared_ptr<VertexBuffer> OpenGL_VertexArray::getVertexBuffer() const
	{
		return m_vertexBuffer;
	}
	std::shared_ptr<IndexBuffer> OpenGL_VertexArray::getIndexBuffer() const
	{
		return m_indexBuffer;
	}
	unsigned int OpenGL_VertexArray::getDrawCount() const
	{
		return 0;
	}
}