#pragma once

namespace Engine
{
	class IndexBuffer
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual unsigned int getSize() const = 0;
		static IndexBuffer* create(unsigned int* indices, unsigned int size);
	};
}
