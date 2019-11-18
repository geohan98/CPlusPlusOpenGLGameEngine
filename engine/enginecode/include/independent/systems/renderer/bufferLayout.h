#pragma once
#include <vector>
#include <initializer_list>
#include <string>

namespace Engine
{
	enum class ShaderDataType
	{
		None = 0, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, Bool, Sampler2D
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Engine::ShaderDataType::Int:		return 4;
		case Engine::ShaderDataType::Int2:		return 4 * 2;
		case Engine::ShaderDataType::Int3:		return 4 * 3;
		case Engine::ShaderDataType::Int4:		return 4 * 4;
		case Engine::ShaderDataType::Float:		return 4;
		case Engine::ShaderDataType::Float2:	return 4 * 2;
		case Engine::ShaderDataType::Float3:	return 4 * 3;
		case Engine::ShaderDataType::Float4:	return 4 * 4;
		case Engine::ShaderDataType::Mat3:		return 4 * 3 * 3;
		case Engine::ShaderDataType::Mat4:		return 4 * 4 * 4;
		case Engine::ShaderDataType::Bool:		return 1;
		case Engine::ShaderDataType::Sampler2D:	return 1;
		}
	}

	static ShaderDataType GLSLStrToSDT(const std::string& glslSrc)
	{

	}

	static unsigned int ShaderDataTypeComponentCount(ShaderDataType)
	{

	}

	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;

		BufferElement() {};
		BufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {}
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
}