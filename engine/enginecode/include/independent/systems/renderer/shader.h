#pragma once
#include <map>

namespace Engine
{
	class BufferLayout; 
	using UniformLayout = std::map<std::string, void *>;

	class Shader
	{
	public:
		virtual unsigned int id() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual bool uploadData(const std::string& name, void * data) = 0;
		virtual bool uploadData(const UniformLayout& uniforms) = 0;
		virtual BufferLayout getBufferLayout() const = 0;
		virtual UniformLayout getUniformLayout() const = 0;

		static Shader* create(const std::string& filepath);
		static Shader* create(const std::string& vertexFilePath,const std::string& fragmentFilePath);
	};
}