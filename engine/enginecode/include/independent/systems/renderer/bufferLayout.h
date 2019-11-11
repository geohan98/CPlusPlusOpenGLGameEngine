/*#pragma once
#include <vector>
#include <initializer_list>

namespace Engine
{
	enum class ShaderDataType
	{
		None = 0, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, Bool, Sampler2D
	};

	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;

		BufferElement() {};
		BufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(ShaderDataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {}
	};

	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_elements;
		unsigned int m_stride;
		void calcStrideAndOffset();
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		inline unsigned int getStride() const { return m_stride; }
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin()const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end()const { return m_elements.end(); }
		void addElement(ShaderDataType datatype)
		{
			m_elements.push_back(BufferElement(datatype));
			calcStrideAndOffset();
		}
	};
}*/