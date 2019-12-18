

namespace Engine
{
	class VertexBufferLayout;

	class VertexBuffer
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void edit(float* vertices, unsigned int size, unsigned int offset) = 0;
		virtual const VertexBufferLayout& getLayout() const = 0;

		static VertexBuffer* create(float* vertices, unsigned int size, VertexBufferLayout& layout);
	};
}