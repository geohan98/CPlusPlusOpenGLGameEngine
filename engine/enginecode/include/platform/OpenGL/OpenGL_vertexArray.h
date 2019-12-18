
#include "systems/renderer/vertexArray.h"

namespace Engine
{

	class OpenGL_VertexArray : public VertexArray
	{
	private:
		unsigned int m_rendererID;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	public:
		OpenGL_VertexArray();
		void bind() override;
		void unbind() override;

		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer) override;

		std::shared_ptr<VertexBuffer> getVertexBuffer() const override;
		std::shared_ptr<IndexBuffer> getIndexBuffer() const override;

		unsigned int getDrawCount() const override;
	};
}