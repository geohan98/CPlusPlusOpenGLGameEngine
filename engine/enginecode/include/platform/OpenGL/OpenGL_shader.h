#pragma once
#include "systems/renderer/shader.h"
#include <string>

namespace Engine
{
	class OpenGL_Shader : public Shader
	{
	private:
		unsigned int program_ID;
	protected:
		std::string parseShader(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string source);
		int getUniformLocation(const std::string name);
	public:
		OpenGL_Shader(const std::string& filepath);
		OpenGL_Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
		unsigned int id() override;
		void bind() override;
		void unbind() override;
		bool uploadData(const std::string& name, void* data) override;
		bool uploadData(const UniformLayout& uniforms) override;
		BufferLayout getBufferLayout() const override;
		UniformLayout getUniformLayout() const override;
	};
}