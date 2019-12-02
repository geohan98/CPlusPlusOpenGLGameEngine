#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include "systems/ButtonCodes.h"

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

	static unsigned int ShaderDataTypeToOpenGL(ShaderDataType type)
	{
		switch (type)
		{
		case Engine::ShaderDataType::Int:			return GL_INT;
		case Engine::ShaderDataType::Int2:			return GL_INT;
		case Engine::ShaderDataType::Int3:			return GL_INT;
		case Engine::ShaderDataType::Int4:			return GL_INT;
		case Engine::ShaderDataType::Float:			return GL_FLOAT;
		case Engine::ShaderDataType::Float2:		return GL_FLOAT;
		case Engine::ShaderDataType::Float3:		return GL_FLOAT;
		case Engine::ShaderDataType::Float4:		return GL_FLOAT;
		case Engine::ShaderDataType::Mat3:			return GL_FLOAT;
		case Engine::ShaderDataType::Mat4:			return GL_FLOAT;
		case Engine::ShaderDataType::Bool:			return GL_BOOL;
		}
	}

	static ShaderDataType GLSLStrToSDT(const std::string& glslSrc)
	{
		ShaderDataType result = ShaderDataType::None;
		if (glslSrc == "bool") result = ShaderDataType::Bool;
		if (glslSrc == "int") result = ShaderDataType::Int;
		if (glslSrc == "ivec2") result = ShaderDataType::Int2;
		if (glslSrc == "ivec3") result = ShaderDataType::Int3;
		if (glslSrc == "ivec4") result = ShaderDataType::Int4;
		if (glslSrc == "float") result = ShaderDataType::Float;
		if (glslSrc == "vec2") result = ShaderDataType::Float2;
		if (glslSrc == "vec3") result = ShaderDataType::Float3;
		if (glslSrc == "vec4") result = ShaderDataType::Float4;
		if (glslSrc == "mat3") result = ShaderDataType::Mat3;
		if (glslSrc == "mat4") result = ShaderDataType::Mat4;
		if (glslSrc == "sampler2D") result = ShaderDataType::Sampler2D;

		return result;
	}

	static unsigned int ShaderDataTypeComponentCount(ShaderDataType type)
	{
		switch (type)
		{
		case Engine::ShaderDataType::Int:			return 1;
		case Engine::ShaderDataType::Int2:			return 2;
		case Engine::ShaderDataType::Int4:			return 4;
		case Engine::ShaderDataType::Float:			return 1;
		case Engine::ShaderDataType::Float2:		return 2;
		case Engine::ShaderDataType::Float3:		return 3;
		case Engine::ShaderDataType::Float4:		return 4;
		case Engine::ShaderDataType::Mat3:			return 3 * 3;
		case Engine::ShaderDataType::Mat4:			return 4 * 4;
		case Engine::ShaderDataType::Bool:			return 1;
		case Engine::ShaderDataType::Sampler2D:		return 1;
		}
	}

	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;


		BufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {}
	};

	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_elements;
		unsigned int m_stride = 0;
		void calcStrideAndOffset();
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		inline unsigned int getStride() const { return m_stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
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