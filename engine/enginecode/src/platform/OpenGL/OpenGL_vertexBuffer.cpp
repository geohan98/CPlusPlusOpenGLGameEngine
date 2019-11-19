#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_vertexBuffer.h"
#include "glad/glad.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_bufferLayout.h"

namespace Engine
{
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(float* vertices, unsigned int size, BufferLayout& layout)
	{
		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		for (unsigned i = 0; i < layout.GetElements().size(); i++)
		{
			const auto& element = layout.GetElements()[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, ShaderDataTypeSize(element.m_dataType), ShaderDataTypeToOpenGL(element.m_dataType), element.m_normalized, layout.getStride(), (const void*)element.m_offset);
		}
	}
	void OpenGL_VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}
	void OpenGL_VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGL_VertexBuffer::edit(float* vertices, unsigned int size, unsigned int offset)
	{
	}
	const BufferLayout& OpenGL_VertexBuffer::getLayout() const
	{
		return OpenGL_BufferLayout();
	}
}