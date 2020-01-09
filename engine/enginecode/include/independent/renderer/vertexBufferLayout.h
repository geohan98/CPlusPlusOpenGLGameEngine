#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include "renderer/shaderDataType.h"
#include "systems/ButtonCodes.h"

namespace Engine
{
	/**
	 *  Vertex Buffer Element
	 */
	class VertexBufferElement
	{
	public:
		ShaderDataType m_dataType; ///< Data Type 
		unsigned int m_size;	   ///<	Size of the data block
		unsigned int m_offset;	   ///<	offset from last data block
		bool m_normalized;		   ///<	is it normalized

		VertexBufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {} ///< Constructor
	};
	/**
	 *  Vertex Buffer Layout
	 */
	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> m_elements;	///< Elements in Buffer
		unsigned int m_stride = 0;						///< Stride of entire data block
		void calcStrideAndOffset();						///< Calculate Stride and Offset
	public:
		VertexBufferLayout() {};																					///< Default Constructor
		VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements);								///< Constructor
		inline unsigned int getStride() const { return m_stride; }													///< Returns the Stride
		inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }					///< Returns the ELemenst of the Buffer
		std::vector<VertexBufferElement>::iterator begin() { return m_elements.begin(); }							///< Returns an iterator to the beginning of the elements
		std::vector<VertexBufferElement>::iterator end() { return m_elements.end(); }								///< Returns an iterator to the end of the elements
		std::vector<VertexBufferElement>::const_iterator begin()const { return m_elements.begin(); }				///< Returns an const iterator to the beginning of the elements
		std::vector<VertexBufferElement>::const_iterator end()const { return m_elements.end(); }					///< Returns an const iterator to the end of the elements
		void addElement(ShaderDataType datatype)																	///< Add an element to the element vector
		{
			m_elements.push_back(VertexBufferElement(datatype));
			calcStrideAndOffset();
		}
	};
}