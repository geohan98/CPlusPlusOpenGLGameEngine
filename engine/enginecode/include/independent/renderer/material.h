#pragma once
#include <memory>
#include <variant>
#include <map>
#include <string>

#include "renderer/shader.h"
#include "renderer/vertexArray.h"
#include "renderer/vertexBuffer.h"


namespace Engine
{
	/**
	 *  Material
	 */
	class Material
	{
	public:
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0; ///< Set the shader for the material
		virtual void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0; ///< set the geometry for the material
		virtual void setDataBlock(const std::map<std::string, void*>& data) = 0; ///< set all the data for the material
		virtual void setDataElement(const std::string& dataName, void* data) = 0; ///< set a single piece of data
		virtual void setVertexData(float* vertices, unsigned int size, unsigned int offset) = 0; ///< set vertex data, Not Implemented

		virtual std::shared_ptr<Shader> getShader() = 0; ///< Return The Shader
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() = 0; ///< Return the Geometry
		virtual std::map<std::string, void* > getData() = 0; ///< Return the Data for the material

		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray); ///< Create API Specific Object
		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexBuufer); ///< Create API Specific Object
	};
}