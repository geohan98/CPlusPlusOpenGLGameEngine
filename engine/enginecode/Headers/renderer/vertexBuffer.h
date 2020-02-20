#pragma once

namespace Engine
{
	namespace Renderer {
		class VertexBufferLayout;
		/**
		 *  Vertex Buffer
		 */
		class VertexBuffer
		{
		public:
			virtual void bind() = 0;		///< Make this the active buffer
			virtual void unbind() = 0;		///< Make this not the active buffer
			virtual void edit(float* vertices, unsigned int size, unsigned int offset) = 0; ///< Not Implemented
			virtual const VertexBufferLayout& getLayout() const = 0; ///< Return the buffer layout

			virtual unsigned int getDrawCount() const = 0;

			static VertexBuffer* create(float* vertices, unsigned int size, VertexBufferLayout& layout); ///< Create API Specific Object
		};
	}
}