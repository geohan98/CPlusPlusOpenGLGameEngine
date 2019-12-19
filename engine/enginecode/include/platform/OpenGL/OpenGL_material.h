#pragma once
#include "renderer/material.h"

namespace Engine
{
	class OpenGL_Material : public Material
	{

	public:
		OpenGL_Material(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& vertexArray);
		void init(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& vertexArray);
		void setShader(const std::shared_ptr<Shader>& shader) override;
		void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override;
		void setDataBlock(const std::map<std::string, void*>& data) override;
		void setDataElement(const std::string& dataName, void* data) override;
		void setVertexData(float* vertices, unsigned int size, unsigned int offset) override;

		inline std::shared_ptr<Shader> getShader() override { return m_shader; }
		inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() override { return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_geomertry); }
		inline std::map<std::string, void*> getData() override { return m_data; }
	private:
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexArray> m_geomertry;
		std::map < std::string, void* > m_data;
	};
}