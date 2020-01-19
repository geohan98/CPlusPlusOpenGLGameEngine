#include "engine_pch.h"
#include "systems/log.h"

#include "systems/resourceManager.h"

namespace Engine
{
	namespace Systems {
		AssetManager<IndexBuffer> ResourceManager::m_indexBuffersObjects;
		AssetManager<Shader> ResourceManager::m_shaders;
		AssetManager<Texture> ResourceManager::m_textures;
		AssetManager<VertexArray> ResourceManager::m_vertexArrayObjects;
		AssetManager<VertexBuffer> ResourceManager::m_vertexBufferObjects;
		AssetManager<Material> ResourceManager::m_materials;
		AssetManager<UniformBuffer> ResourceManager::m_uniformBuffers;

		std::string ResourceManager::parseFilePath(const std::string& str)
		{
			std::string x = str;
			x = x.substr(x.find_last_of("/") + 1);
			x = x.erase(x.find("."));
			return x;
		}

		void ResourceManager::start(SystemSignal init, ...)
		{

		}

		void ResourceManager::stop(SystemSignal close, ...)
		{

		}

		//INDEX BUFFERS

		std::shared_ptr<IndexBuffer> ResourceManager::addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count)
		{
			m_indexBuffersObjects.add(name, std::shared_ptr<IndexBuffer>(IndexBuffer::create(indices, count)));
			return m_indexBuffersObjects.get(name);
		}

		std::shared_ptr<IndexBuffer> ResourceManager::getIndexBuffer(const std::string& name)
		{
			return m_indexBuffersObjects.get(name);
		}

		bool ResourceManager::doesIndexBufferExist(const std::string& name)
		{
			return m_indexBuffersObjects.contains(name);
		}

		//SHADERS

		std::shared_ptr<Shader> ResourceManager::addShader(const std::string& filepath)
		{
			m_shaders.add(parseFilePath(filepath), std::shared_ptr<Shader>(Shader::create(filepath)));
			return m_shaders.get(parseFilePath(filepath));
		}

		std::shared_ptr<Shader> ResourceManager::getShader(const std::string& filepath)
		{
			return m_shaders.get(parseFilePath(filepath));;
		}

		bool ResourceManager::doesShaderExist(const std::string& filepath)
		{
			return m_shaders.contains(filepath);
		}

		//TEXTURES

		std::shared_ptr<Texture> ResourceManager::addTexture(const std::string& filepath)
		{
			m_textures.add(parseFilePath(filepath), std::shared_ptr<Texture>(Texture::createFromFile(filepath)));
			return m_textures.get(parseFilePath(filepath));
		}

		std::shared_ptr<Texture> ResourceManager::addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData)
		{
			m_textures.add(name, std::shared_ptr<Texture>(Texture::createFromRawData(width, height, channels, texData)));
			return m_textures.get(name);
		}

		std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& filepath)
		{
			return m_textures.get(parseFilePath(filepath));
		}

		bool ResourceManager::doesTextureExist(const std::string& filepath)
		{
			return m_textures.contains(filepath);
		}

		//VERTEX ARRAYS

		std::shared_ptr<VertexArray> ResourceManager::addVertexArray(const std::string& name)
		{
			m_vertexArrayObjects.add(name, std::shared_ptr<VertexArray>(VertexArray::create()));
			return m_vertexArrayObjects.get(name);
		}

		std::shared_ptr<Engine::VertexArray> ResourceManager::getVertexArray(const std::string& name)
		{
			return m_vertexArrayObjects.get(name);
		}

		bool ResourceManager::doesVertexArrayExist(const std::string& name)
		{
			return m_vertexArrayObjects.contains(name);
		}

		//VERTEX BUFFERS

		std::shared_ptr<Engine::VertexBuffer> ResourceManager::addVertexBuffer(const std::string& name, float* vertices, unsigned int size, VertexBufferLayout& layout)
		{
			m_vertexBufferObjects.add(name, std::shared_ptr<VertexBuffer>(VertexBuffer::create(vertices, size, layout)));
			return m_vertexBufferObjects.get(name);
		}

		std::shared_ptr<Engine::VertexBuffer> ResourceManager::getVertexBuffer(const std::string& name)
		{
			return m_vertexBufferObjects.get(name);
		}

		bool ResourceManager::doesVertexBufferExist(const std::string& name)
		{
			return m_vertexBufferObjects.contains(name);
		}

		//MATERIALS

		std::shared_ptr<Material> ResourceManager::addMaterial(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> vertexArray)
		{
			m_materials.add(name, std::shared_ptr<Material>(Material::create(shader, vertexArray)));
			return m_materials.get(name);
		}

		std::shared_ptr<Material> ResourceManager::getMaterial(const std::string& name)
		{
			return m_materials.get(name);
		}

		bool ResourceManager::doesMaterialExist(const std::string& name)
		{
			return m_materials.contains(name);
		}

		std::shared_ptr<Engine::UniformBuffer> ResourceManager::addUniformBuffer(const std::string& name, unsigned int size, UniformBufferLayout& layout)
		{
			m_uniformBuffers.add(name, std::shared_ptr<UniformBuffer>(UniformBuffer::create(size, layout)));
			return m_uniformBuffers.get(name);
		}

		std::shared_ptr<Engine::UniformBuffer> ResourceManager::getUniformBuffer(const std::string& name)
		{
			return m_uniformBuffers.get(name);
		}

		bool ResourceManager::doesUniformBufferExist(const std::string& name)
		{
			return m_uniformBuffers.contains(name);
		}

	}
}