#pragma once
#include "systems/renderer/shader.h"
#include "systems/renderer/bufferLayout.h"
#include <string>

namespace Engine
{
	class OpenGL_Shader : public Shader
	{
	private:
		unsigned int m_program_ID;
		BufferLayout m_bufferlayout;
		UniformLayout m_uniformLayout;
		void parseSource(const std::string& filepath);
		void compileAndLink(std::string& vertex, std::string& fragment);
		void setUniformLocations();
	public:
		OpenGL_Shader(const std::string& filepath);
		OpenGL_Shader(const std::string& vertex, const std::string& fragment);
		unsigned int id() override;
		void bind() override;
		void unbind() override;
		bool uploadData(const std::string& name, void* data) override;
		bool uploadData(const UniformLayout& uniforms) override;
		BufferLayout getBufferLayout() const override;
		UniformLayout getUniformLayout() const override;
	};
}