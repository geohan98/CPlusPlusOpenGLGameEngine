
#include <memory>
#include <variant>
#include <map>
#include <string>

#include "systems/renderer/shader.h"
#include "systems/renderer/vertexArray.h"
#include "systems/renderer/vertexBuffer.h"


namespace Engine
{
	class Material
	{
	public:
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0;
		virtual void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0;
		virtual void setDataBlock(const std::map<std::string, void*>& data) = 0;
		virtual void setDataElement(const std::string& dataName, void* data) = 0;
		virtual void setVertexData(float* vertices, unsigned int size, unsigned int offset) = 0;

		virtual std::shared_ptr<Shader> getShader() = 0;
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() = 0;
		virtual std::map<std::string, void* > getData() = 0;

		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexBuufer);
	};
}