#pragma once
#include <string>
#include "renderer/uniformBufferLayout.h"
#include "renderer/shader.h"

namespace Engine
{
	/**
	 *  Uniform Buffer
	 */
	class UniformBuffer
	{
	public:
		virtual void bind() = 0;	///< Make this the active buffer
		virtual void unbind() = 0;	///< Make this not the active buffer
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) = 0; ///< Attach a shader to this uniform buffer
		virtual void setData(unsigned int offset, unsigned int size, void* data) = 0; ///< Set the data for Uniform Buffer
		virtual UniformBufferLayout getLayout() const = 0; ///< Return the layout of the uniform buffer

		static UniformBuffer* create(unsigned int size, UniformBufferLayout& layout); ///< Create API Specific Object
		static UniformBuffer* create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout); ///< Create API Specific Object
	};
}