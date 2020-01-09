#pragma once
#include "renderer/shader.h"
#include "renderer/vertexBufferLayout.h"
#include <string>

namespace Engine
{
	/**
	 * GL Shader
	 */
	class OpenGL_Shader : public Shader
	{
	private:
		unsigned int m_program_ID; ///< Object ID
		VertexBufferLayout m_bufferlayout; ///< A Vertex Buffer Layout for the Shader
		UniformLayout m_uniformLayout; ///< A uniform Layout
		std::map<std::string, std::pair<ShaderDataType, int>> m_uniformLocationCache; ///< string void pointer pairs
		void parseSource(const std::string& filepath); ///< parse the source file into strings
		void compileAndLink(std::string& vertex, std::string& fragment); ///< Create Shader Program
		void setUniformLocations(); ///< Set the location of the uniforms in the cache
		void dispatchUniformUpload(ShaderDataType type, unsigned int location, void* data); ///< Sends a uniform to the shader
	public:
		OpenGL_Shader(const std::string& filepath); ///< Constructor
		OpenGL_Shader(const std::string& vertex, const std::string& fragment); ///< Constructor
		unsigned int id() override; ///< get prog id
		void bind() override; ///< Bind the shader
		void unbind() override; ///< Unbind the shader
		bool uploadData(const std::string& name, void* data) override; ///< upload a single uniform
		bool uploadData(const UniformLayout& uniforms) override; ///< upload a whole uniform layout
		VertexBufferLayout getBufferLayout() const override; ///< return buffer layout
		UniformLayout getUniformLayout() const override; ///< return uniform layout
	};
}