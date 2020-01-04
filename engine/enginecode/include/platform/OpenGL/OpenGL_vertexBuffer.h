#pragma once
#include "renderer/vertexBuffer.h"
#include "renderer/vertexBufferLayout.h"

namespace Engine
{
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_rendererID;
		VertexBufferLayout m_layout;
	public:
		OpenGL_VertexBuffer(float* vertices, unsigned int count, VertexBufferLayout& layout);
		void bind() override;
		void unbind() override;
		void edit(float* vertices, unsigned int size, unsigned int offset) override;
		const VertexBufferLayout& getLayout() const override;
	};
}