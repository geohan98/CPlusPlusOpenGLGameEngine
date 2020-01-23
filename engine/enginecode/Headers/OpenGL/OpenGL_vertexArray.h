#pragma once
#include "../enginecode/Headers/renderer/vertexArray.h"

namespace Engine
{
	namespace Renderer {
		/**
		 * GL Vertex Array
		 */
		class OpenGL_VertexArray : public VertexArray
		{
		private:
			unsigned int m_rendererID; ///< Object ID
			std::shared_ptr<VertexBuffer> m_vertexBuffer; ///< Pointer to a vertex buffer
			std::shared_ptr<IndexBuffer> m_indexBuffer; ///< Pointer to a Index Buffer
		public:
			OpenGL_VertexArray(); ///< Constructor
			void bind() override; ///< Bind the vertex Array
			void unbind() override; ///< Unbind the vertex Array

			void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; ///< set the vertex buffer
			void setIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer) override; ///< set the index buffer

			std::shared_ptr<VertexBuffer> getVertexBuffer() const override; ///< return the vertex buffer
			std::shared_ptr<IndexBuffer> getIndexBuffer() const override; ///< return the index buffer

			unsigned int getDrawCount() const override; ///< return the index buffer indices count
		};
	}
}