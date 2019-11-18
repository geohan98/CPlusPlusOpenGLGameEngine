#pragma once
#include "systems/renderer/indexBuffer.h"

namespace Engine
{
	class OpenGL_IndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_RendererID;
	public:
		OpenGL_IndexBuffer(unsigned int* indices, unsigned int size);
		void bind() override;
		void unbind() override;
		unsigned int getSize() const override;
	};
}