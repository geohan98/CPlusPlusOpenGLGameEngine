
#include "systems/renderer/indexBuffer.h"

namespace Engine
{
	class OpenGL_IndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		OpenGL_IndexBuffer(unsigned int* indices, unsigned int count);
		void bind() override;
		void unbind() override;
		unsigned int getCount() const override;
	};
}