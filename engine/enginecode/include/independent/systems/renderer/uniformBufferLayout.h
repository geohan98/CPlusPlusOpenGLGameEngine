#include <vector>
#include <memory>
#include "systems/renderer/shaderDataType.h"

namespace Engine
{
	class UniformBufferElement
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;

		UniformBufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {}
	};

	class UniformBufferLayout
	{
	private:
		std::vector<UniformBufferElement> m_elements;
		unsigned int m_stride = 0;
		void calcStrideAndOffset();
	public:
		UniformBufferLayout() {};
		UniformBufferLayout(const std::initializer_list<UniformBufferElement>& elements);
		inline unsigned int getStride() const { return m_stride; }
		inline const std::vector<UniformBufferElement>& GetElements() const { return m_elements; }
		std::vector<UniformBufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<UniformBufferElement>::iterator end() { return m_elements.end(); }
		std::vector<UniformBufferElement>::const_iterator begin()const { return m_elements.begin(); }
		std::vector<UniformBufferElement>::const_iterator end()const { return m_elements.end(); }
		void addElement(ShaderDataType datatype)
		{
			m_elements.push_back(UniformBufferElement(datatype));
			calcStrideAndOffset();
		}
	};
}