#include "engine_pch.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_uniformBuffer.h"
#include <glad/glad.h>

namespace Engine
{

	OpenGL_UniformBuffer::OpenGL_UniformBuffer(unsigned int size, UniformBufferLayout& layout) : m_layout(layout), m_bindingPoint(0)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, m_bindingPoint, m_id, 0, size);
	}

	void OpenGL_UniformBuffer::bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	}

	void OpenGL_UniformBuffer::unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGL_UniformBuffer::attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName)
	{
		unsigned int uniformBlockIndex = glGetUniformBlockIndex(shader->id(), blockName.c_str());
#ifdef NG_DEBUG
		LOG_CORE_INFO("UNIFORM BUFFER: ATTACH SHADER BLOCK INDEX {0}", uniformBlockIndex);
#endif // NG_DEBUG

		glUniformBlockBinding(shader->id(), uniformBlockIndex, m_bindingPoint);
	}

	void OpenGL_UniformBuffer::setData(unsigned int offset, unsigned int size, void* data)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	Engine::UniformBufferLayout OpenGL_UniformBuffer::getLayout() const
	{
		return m_layout;
	}

}