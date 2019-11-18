#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_indexBuffer.h"
#include "glad/glad.h"
#include "systems/log.h"

namespace Engine
{
	OpenGL_IndexBuffer::OpenGL_IndexBuffer(unsigned int* indices, unsigned int size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	void OpenGL_IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGL_IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	unsigned int OpenGL_IndexBuffer::getSize() const
	{
		return 0;
	}
}