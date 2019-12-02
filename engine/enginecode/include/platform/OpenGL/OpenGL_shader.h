#pragma once
#include "systems/renderer/shader.h"

namespace Engine
{
	class OpenGL_Shader : public Shader
	{
	private:
		unsigned int program_ID;
		OpenGL_Shader();
	public:
		unsigned int id() override;
		void bind() override;
		void unbind() override;
		bool uploadData(const std::string& name, void * data) override;
		bool uploadData(const UniformLayout& uniforms) override;
		BufferLayout getBufferLayout() const override;
		UniformLayout getUniformLayout() const override;
	};
}