#include "engine_pch.h"
#include "../enginecode/Headers/OpenGL/OpenGL_indexBuffer.h"
#include <glad/glad.h>
#include "../enginecode/Headers/systems/log.h"

namespace Engine
{
	namespace Renderer {
		OpenGL_IndexBuffer::OpenGL_IndexBuffer(unsigned int* indices, unsigned int count) : m_Count(count)
		{
			glCreateBuffers(1, &m_RendererID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}
		void OpenGL_IndexBuffer::bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		}
		void OpenGL_IndexBuffer::unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		unsigned int OpenGL_IndexBuffer::getCount() const
		{
			return m_Count;
		}
	}
}