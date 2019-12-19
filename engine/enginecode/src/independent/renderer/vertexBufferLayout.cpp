#include "engine_pch.h"
#include "renderer/vertexBufferLayout.h"
#include "systems/ButtonCodes.h"

namespace Engine
{
	void VertexBufferLayout::calcStrideAndOffset()
	{
		unsigned int previousOffset = 0;

		for (unsigned i = 0; i < m_elements.size(); i++)
		{
			m_elements[i].m_offset = previousOffset;
			previousOffset += ShaderDataTypeSize(m_elements[i].m_dataType);
		}
		m_stride = previousOffset;
	}
	VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements) : m_elements(elements)
	{
		calcStrideAndOffset();
	}

}