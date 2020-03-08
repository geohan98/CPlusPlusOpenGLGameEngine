#include "engine_pch.h"
#include "../enginecode/Headers/OpenGL/OpenGL_indexBuffer.h"
#include <glad/glad.h>
#include "../enginecode/Headers/systems/log.h"

namespace Engine
{
	namespace Renderer {
		OpenGL_IndexBuffer::OpenGL_IndexBuffer(unsigned int* indices, unsigned int count) : m_count(count)
		{
			glCreateBuffers(1, &m_rendererID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
			LOG_CORE_INFO("[OpenGL][INDEX BUFFER][INDEX BUFFER CREAETD WITH ID:{0}]", m_rendererID);
		}
		OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
		{
			glDeleteBuffers(1, &m_rendererID);
			LOG_CORE_INFO("[OpenGL][INDEX BUFFER][INDEX BUFFER DESTROYED WITH ID:{0}]", m_rendererID);
		}
		void OpenGL_IndexBuffer::bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		}
		void OpenGL_IndexBuffer::unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		unsigned int OpenGL_IndexBuffer::getCount() const
		{
			return m_count;
		}
	}
}