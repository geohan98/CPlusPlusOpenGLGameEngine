#pragma once
#include <vector>
#include <memory>
#include "renderer/shaderDataType.h"

namespace Engine
{
	namespace Renderer {
		/**
		 *  Uniform Buffer Element
		 */
		class UniformBufferElement
		{
		public:
			ShaderDataType m_dataType; ///< Data Type 
			unsigned int m_size;	   ///< Size of the data block
			unsigned int m_offset;	   ///< offset from last data block
			bool m_normalized;		   ///< is it normalized

			UniformBufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {} ///< Constructor
		};
		/**
		 *  Uniform Buffer Layout
		 */
		class UniformBufferLayout
		{
		private:
			std::vector<UniformBufferElement> m_elements;														///< Elements of the buffer
			unsigned int m_stride = 0;																			///< The size of all the elements
			void calcStrideAndOffset();																			///< Calculate stride and offset
		public:
			UniformBufferLayout() {};																			///< Default Constructor
			UniformBufferLayout(const std::initializer_list<UniformBufferElement>& elements);					///< Constructor
			inline unsigned int getStride() const { return m_stride; }											///< Returns the Stride
			inline const std::vector<UniformBufferElement>& GetElements() const { return m_elements; }			///< Returns the ELemenst of the Buffer
			std::vector<UniformBufferElement>::iterator begin() { return m_elements.begin(); }					///< Returns an iterator to the beginning of the elements
			std::vector<UniformBufferElement>::iterator end() { return m_elements.end(); }						///< Returns an iterator to the end of the elements
			std::vector<UniformBufferElement>::const_iterator begin()const { return m_elements.begin(); }		///< Returns an const iterator to the beginning of the elements
			std::vector<UniformBufferElement>::const_iterator end()const { return m_elements.end(); }			///< Returns an const iterator to the end of the elements
			void addElement(ShaderDataType datatype)															///< Add an element to the element vector
			{
				m_elements.push_back(UniformBufferElement(datatype));
				calcStrideAndOffset();
			}
		};
	}
}