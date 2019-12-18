#include <string>
#include "systems/renderer/uniformBufferLayout.h"
#include "systems/renderer/shader.h"

namespace Engine
{

	class UniformBuffer
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) = 0;
		virtual void setData(unsigned int offset, unsigned int size, void* data) = 0;
		virtual UniformBufferLayout getLayout() const = 0;

		static UniformBuffer* create(unsigned int size, UniformBufferLayout& layout);
		static UniformBuffer* create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout);
	};
}