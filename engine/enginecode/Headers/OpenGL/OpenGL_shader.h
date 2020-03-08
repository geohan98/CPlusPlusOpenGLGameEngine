#pragma once
#include "../enginecode/Headers/renderer/shader.h"
#include "../enginecode/Headers/renderer/vertexBufferLayout.h"
#include <string>

namespace Engine
{
	namespace Renderer {
		/**
		 * GL Shader
		 */
		class OpenGL_Shader : public Shader
		{
		private:
			unsigned int m_rendererID; ///< Object ID
			VertexBufferLayout m_bufferlayout; ///< A Vertex Buffer Layout for the Shader
			UniformLayout m_uniformLayout; ///< A uniform Layout
			std::map<std::string, std::pair<ShaderDataType, int>> m_uniformLocationCache; ///< string void pointer pairs

			void parseSource(const std::string& filepath); ///< parse the source file into strings
			void compileAndLink(std::string& vertex, std::string& fragment, std::string& geomatry, std::string& tessalationControl, std::string& tessalationEvaluation); ///< Create Shader Program
			bool checkCompileErrors(unsigned int shader, bool program);
			void setUniformLocations(); ///< Set the location of the uniforms in the cache
			void dispatchUniformUpload(ShaderDataType type, unsigned int location, void* data); ///< Sends a uniform to the shader
		public:
			OpenGL_Shader(const std::string& filepath); ///< Constructor
			~OpenGL_Shader();

			unsigned int getId() override; ///< get prog id
			void bind() override; ///< Bind the shader
			void unbind() override; ///< Unbind the shader
			bool uploadData(const std::string& name, void* data) override; ///< upload a single uniform
			VertexBufferLayout getBufferLayout() const override; ///< return buffer layout
			UniformLayout getUniformLayout() const override; ///< return uniform layout
		};
	}
}