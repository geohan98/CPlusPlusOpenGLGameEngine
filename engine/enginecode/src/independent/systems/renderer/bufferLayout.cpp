#include "engine_pch.h"
#include "systems/renderer/bufferLayout.h"
#include "systems/ButtonCodes.h"

namespace Engine
{
	void BufferLayout::calcStrideAndOffset()
	{
		unsigned int previousOffset = 0;

		for (unsigned i = 0; i < m_elements.size(); i++)
		{
			m_elements[i].m_offset = previousOffset;
			previousOffset += ShaderDataTypeSize(m_elements[i].m_dataType);
		}
		m_stride = previousOffset;
	}
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements)
	{
		calcStrideAndOffset();
	}

}