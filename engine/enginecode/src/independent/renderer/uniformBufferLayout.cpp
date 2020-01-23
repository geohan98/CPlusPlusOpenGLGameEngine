#include "engine_pch.h"
#include "systems/log.h"
#include "renderer/uniformBuffer.h"

namespace Engine
{
	namespace Renderer {
		void UniformBufferLayout::calcStrideAndOffset()
		{
			unsigned int previousOffset = 0;

			for (unsigned i = 0; i < m_elements.size(); i++)
			{
				m_elements[i].m_offset = previousOffset;
				previousOffset += ShaderDataTypeSize(m_elements[i].m_dataType);

				int remainder = previousOffset % 16;
				if (remainder != 0)
				{
					previousOffset = previousOffset + 16 - remainder;
				}
			}
			m_stride = previousOffset;
		}

		UniformBufferLayout::UniformBufferLayout(const std::initializer_list<UniformBufferElement>& elements) : m_elements(elements)
		{
			calcStrideAndOffset();
		}

	}
}