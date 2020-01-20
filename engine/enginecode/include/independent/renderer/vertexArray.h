#pragma once
#include <vector>

namespace Engine
{
	namespace Renderer {
		class VertexBuffer;
		class IndexBuffer;
		/**
		 *  Vertex Array
		 */
		class VertexArray
		{
		public:
			virtual void bind() = 0;																///< Make this the active buffer
			virtual void unbind() = 0;																///< Make this not the active buffer

			virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;	///< set the Vertex Buffer
			virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer) = 0;		///< set the Index Buffer

			virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;						///< return Vertex Buffer
			virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;						///< return Index Buffer

			virtual unsigned int getDrawCount() const = 0;											///< return number of indices in index buffer

			static VertexArray* create();															///< Create API Specific Object

		};
	}
}
