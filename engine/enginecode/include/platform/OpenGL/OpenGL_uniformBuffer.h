#pragma once
#include "renderer/uniformBuffer.h"

namespace Engine
{
	/**
	 * GL Uniform Buffer
	 */
	class OpenGL_UniformBuffer : public UniformBuffer
	{
	private:
		unsigned int m_id; ///< Object Id
		UniformBufferLayout m_layout; ///< Uniform Buffer Layout
		unsigned int m_bindingPoint; ///< Binding Point
	public:
		OpenGL_UniformBuffer(unsigned int size, UniformBufferLayout& layout); ///< Constructor
		void bind() override; ///< Bind the uniform buffer
		void unbind() override; ///< Unbind the uniform buffer
		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) override; ///< attach a shader block
		void setData(unsigned int offset, unsigned int size, void* data) override; ///< set the data for the uniform buffer
		UniformBufferLayout getLayout() const override; ///< return the layout of the buffer
	};
}