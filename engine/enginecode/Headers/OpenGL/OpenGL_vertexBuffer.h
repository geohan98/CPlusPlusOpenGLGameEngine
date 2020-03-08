#pragma once
#include "../enginecode/Headers/renderer/vertexBuffer.h"
#include "../enginecode/Headers/renderer/vertexBufferLayout.h"

namespace Engine
{
	namespace Renderer {
		/**
		 * GL Vertex Buffer
		 */
		class OpenGL_VertexBuffer : public VertexBuffer
		{
		private:
			unsigned int m_rendererID; ///< object id
			unsigned int m_drawCount;
			VertexBufferLayout m_layout; ///< buffer layout
		public:
			OpenGL_VertexBuffer(float* vertices, unsigned int count, VertexBufferLayout& layout); ///< Constructor
			~OpenGL_VertexBuffer();
			void bind() override; ///< Bind the vertex buffer
			void unbind() override; ///< Unbind the vertex buffer
			void edit(float* vertices, unsigned int count) override; ///< Edit the vertex buffer
			const VertexBufferLayout& getLayout() const override; ///< return the layout of the buffer
			unsigned int getDrawCount() const override { return m_drawCount; }
		};
	}
}