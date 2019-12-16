#pragma once
#include "system.h"
#include "assetManager.h"

#include "include/independent/systems/renderer/indexBuffer.h"
#include "include/independent/systems/renderer/shader.h"
#include "include/independent/systems/renderer/texture.h"
#include "include/independent/systems/renderer/vertexBuffer.h"
#include "include/independent/systems/renderer/vertexArray.h"

namespace Engine
{
	class ResourceManager : public System
	{
	private:
		static AssetManager<IndexBuffer> m_indexBuffersObjects;
		static AssetManager<Shader> m_shaders;
		static AssetManager<Texture> m_textures;
		static AssetManager<VertexArray> m_vertexArrayObjects;
		static AssetManager<VertexBuffer> m_vertexBufferObjects;
	public:
		static std::string parseFilePath(const std::string& str);
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;

		static std::shared_ptr<IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);
		static std::shared_ptr<IndexBuffer> getIndexBuffer(const std::string& name);
		static bool doesIndexBufferExist(const std::string& name);

		static std::shared_ptr<Shader> addShader(const std::string& filepath);
		static std::shared_ptr<Shader> getShader(const std::string& filepath);
		static bool doesShaderExist(const std::string& filepath);

		static std::shared_ptr<Texture> addTexture(const std::string& filepath);
		static std::shared_ptr<Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData);
		static std::shared_ptr<Texture> getTexture(const std::string& filepath);
		static bool doesTextureExist(const std::string& filepath);

		static std::shared_ptr<VertexArray> addVertexArray(const std::string& name);
		static std::shared_ptr<VertexArray> getVertexArray(const std::string& name);
		static bool doesVertexArrayExist(const std::string& name);

		static std::shared_ptr<VertexBuffer> addVertexBuffer(const std::string& name, float* vertices, unsigned int size, BufferLayout& layout);
		static std::shared_ptr<VertexBuffer> getVertexBuffer(const std::string& name);
		static bool doesVertexBufferExist(const std::string& name);

	};
}