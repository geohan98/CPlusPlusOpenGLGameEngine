#pragma once
#include "../enginecode/Headers/renderer/uniformBuffer.h"

namespace Engine
{
	namespace Renderer {
		/**
		 * GL Uniform Buffer
		 */
		class OpenGL_UniformBuffer : public UniformBuffer
		{
		private:
			unsigned int m_rendererID; ///< Object Id
			UniformBufferLayout m_layout; ///< Uniform Buffer Layout
			unsigned int m_bindingPoint; ///< Binding Point
			static unsigned int s_bindingPoint; ///< Binding Point Counter
		public:
			OpenGL_UniformBuffer(unsigned int size, UniformBufferLayout& layout); ///< Constructor
			~OpenGL_UniformBuffer();
			void bind() override; ///< Bind the uniform buffer
			void unbind() override; ///< Unbind the uniform buffer
			void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) override; ///< attach a shader block
			void setData(unsigned int offset, unsigned int size, void* data) override; ///< set the data for the uniform buffer
			UniformBufferLayout getLayout() const override; ///< return the layout of the buffer
		};
	}
}