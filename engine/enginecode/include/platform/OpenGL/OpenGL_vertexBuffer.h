#pragma once
#include "systems/renderer/vertexBuffer.h"

namespace Engine
{
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_rendererID;
	public:
		OpenGL_VertexBuffer(float* vertices, unsigned int size, BufferLayout& layout);
		void bind() override;
		void unbind() override;
		void edit(float* vertices, unsigned int size, unsigned int offset) override;
		const BufferLayout& getLayout() const override;
	};
}