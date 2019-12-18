#pragma once
#include "systems/renderer/uniformBuffer.h"

namespace Engine
{
	class OpenGL_UniformBuffer : public UniformBuffer
	{
	private:
		unsigned int m_id;
		UniformBufferLayout m_layout;
		unsigned int m_bindingPoint;
	public:
		OpenGL_UniformBuffer(unsigned int size, UniformBufferLayout& layout);
		void bind() override;
		void unbind() override;
		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) override;
		void setData(unsigned int offset, unsigned int size, void* data) override;
		UniformBufferLayout getLayout() const override;
	};
}