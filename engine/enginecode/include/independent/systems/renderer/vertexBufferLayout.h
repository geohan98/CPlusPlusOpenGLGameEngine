#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include "systems/renderer/shaderDataType.h"
#include "systems/ButtonCodes.h"

namespace Engine
{
	class VertexBufferElement
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;

		VertexBufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {}
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> m_elements;
		unsigned int m_stride = 0;
		void calcStrideAndOffset();
	public:
		VertexBufferLayout() {};
		VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements);
		inline unsigned int getStride() const { return m_stride; }
		inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
		std::vector<VertexBufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<VertexBufferElement>::iterator end() { return m_elements.end(); }
		std::vector<VertexBufferElement>::const_iterator begin()const { return m_elements.begin(); }
		std::vector<VertexBufferElement>::const_iterator end()const { return m_elements.end(); }
		void addElement(ShaderDataType datatype)
		{
			m_elements.push_back(VertexBufferElement(datatype));
			calcStrideAndOffset();
		}
	};
}