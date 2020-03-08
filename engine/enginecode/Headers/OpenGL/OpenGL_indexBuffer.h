#pragma once
#include "../enginecode/Headers/renderer/indexBuffer.h"

namespace Engine
{
	namespace Renderer {
		/**
		 * GL Index Buffer
		 */
		class OpenGL_IndexBuffer : public IndexBuffer
		{
		private:
			unsigned int m_rendererID; ///< Object ID
			unsigned int m_count; ///< Number of indices
		public:
			OpenGL_IndexBuffer(unsigned int* indices, unsigned int count); ///< Constructor
			~OpenGL_IndexBuffer();
			void bind() override; ///< Bind the index Buffer
			void unbind() override; ///< Unbind the index buffer
			unsigned int getCount() const override; ///< Return the number of indices
		};
	}
}