#pragma once
#include <vector>

namespace Engine
{
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer) = 0;

		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;

		virtual unsigned int getDrawCount() const = 0;

		static VertexArray* create();

	};
}
