#include "engine_pch.h"
#include "../enginecode/Headers/OpenGL/OpenGL_vertexBuffer.h"
#include <glad/glad.h>
#include "../enginecode/Headers/systems/log.h"

namespace Engine
{
	namespace Renderer {
		OpenGL_VertexBuffer::OpenGL_VertexBuffer(float* vertices, unsigned int count, VertexBufferLayout& layout) : m_layout(layout), m_drawCount(count)
		{
			glCreateBuffers(1, &m_rendererID);
			glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
			glBufferData(GL_ARRAY_BUFFER, m_drawCount * m_layout.getStride(), vertices, GL_DYNAMIC_DRAW);
			LOG_CORE_INFO("[OpenGL][VERTEX BUFFER][CREATING VERTEX BUFFER, ID:{0}]", m_rendererID);
		}

		OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
		{
			glDeleteBuffers(1, &m_rendererID);
			LOG_CORE_INFO("[OpenGL][VERTEX BUFFER][VERTEX BUFFER DESTROYED WITH ID:{0}]", m_rendererID);
		}

		void OpenGL_VertexBuffer::bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		}

		void OpenGL_VertexBuffer::unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void OpenGL_VertexBuffer::edit(float* vertices, unsigned int count)
		{
			m_drawCount = count;
			glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
			glBufferData(GL_ARRAY_BUFFER, m_drawCount * m_layout.getStride(), vertices, GL_DYNAMIC_DRAW);
		}

		const VertexBufferLayout& OpenGL_VertexBuffer::getLayout() const
		{
			return m_layout;
		}

	}
}