#pragma once
#include "../enginecode/Headers/renderer/material.h"

namespace Engine
{
	namespace Renderer {
		/**
		 * GL Material
		 */
		class OpenGL_Material : public Material
		{

		public:
			OpenGL_Material(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& vertexArray); ///< Constructor
			OpenGL_Material(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexBuffer>& vertexBuffer); ///< Constructor
			void init(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& vertexArray); ///< Initalise
			void setShader(const std::shared_ptr<Shader>& shader) override; ///< set the shader
			void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override; ///< set the vertex data
			void setDataBlock(const std::map<std::string, void*>& data) override; ///< set a single data element
			void setDataElement(const std::string& dataName, void* data) override; ///< set a block of data elements
			void setVertexData(float* vertices, unsigned int size, unsigned int offset) override; ///< set the vertex data

			inline std::shared_ptr<Shader> getShader() override { return m_shader; } ///< return the shader
			inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() override { return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_geomertry); } ///< return the geomatery
			inline std::map<std::string, void*> getData() override { return m_data; } ///< return the map of string data pairs
		private:
			std::shared_ptr<Shader> m_shader; ///< A Shader
			std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> m_geomertry; ///< A Vertex Array
			std::map < std::string, void* > m_data; ///< String data pairs
		};
	}
}