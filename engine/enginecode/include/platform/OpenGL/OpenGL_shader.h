#pragma once
#include "systems/renderer/shader.h"
#include "systems/renderer/vertexBufferLayout.h"
#include <string>

namespace Engine
{
	class OpenGL_Shader : public Shader
	{
	private:
		unsigned int m_program_ID;
		VertexBufferLayout m_bufferlayout;
		UniformLayout m_uniformLayout;
		std::map<std::string, std::pair<ShaderDataType, int>> m_uniformLocationCache;
		void parseSource(const std::string& filepath);
		void compileAndLink(std::string& vertex, std::string& fragment);
		void setUniformLocations();
		void dispatchUniformUpload(ShaderDataType type, unsigned int location, void* data);
	public:
		OpenGL_Shader(const std::string& filepath);
		OpenGL_Shader(const std::string& vertex, const std::string& fragment);
		unsigned int id() override;
		void bind() override;
		void unbind() override;
		bool uploadData(const std::string& name, void* data) override;
		bool uploadData(const UniformLayout& uniforms) override;
		VertexBufferLayout getBufferLayout() const override;
		UniformLayout getUniformLayout() const override;
	};
}