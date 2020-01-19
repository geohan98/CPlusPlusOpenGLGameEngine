#pragma once
#include "system.h"
#include "assetManager.h"

#include "renderer/indexBuffer.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/vertexBuffer.h"
#include "renderer/vertexBufferLayout.h"
#include "renderer/vertexArray.h"
#include "renderer/material.h"
#include "renderer/uniformBuffer.h"

namespace Engine
{
	/**
	 * Resource Manger, Handles resources for the engine
	 */
	class ResourceManager : public System
	{
	private:
		static AssetManager<IndexBuffer> m_indexBuffersObjects;																															///< Index Buffer Asset Manager
		static AssetManager<Shader> m_shaders;																																			///< Shader Asset Manager
		static AssetManager<Texture> m_textures;																																		///< Texture Asset Manager
		static AssetManager<VertexArray> m_vertexArrayObjects;																															///< Vertex Array Asset Manager
		static AssetManager<VertexBuffer> m_vertexBufferObjects;																														///< Vertex Buffer Asset Manager
		static AssetManager<Material> m_materials;																																		///< Material Asset Manager
		static AssetManager<UniformBuffer> m_uniformBuffers;
	public:
		static std::string parseFilePath(const std::string& str);																														///< Remove all but the file name
		void start(SystemSignal init = SystemSignal::None, ...) override;																												///< Start the Resource Manager
		void stop(SystemSignal close = SystemSignal::None, ...) override;																												///< Stop the Resource Manager

		static std::shared_ptr<IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);															///< add a index buffer to the asset manager
		static std::shared_ptr<IndexBuffer> getIndexBuffer(const std::string& name);																									///< get a index buffer from the asset manager
		static bool doesIndexBufferExist(const std::string& name);																														///< does a index buffer already exist with that name

		static std::shared_ptr<Shader> addShader(const std::string& filepath);																											///< add a shader to the asset manager
		static std::shared_ptr<Shader> getShader(const std::string& filepath);																											///< get a shader from the asset manager
		static bool doesShaderExist(const std::string& filepath);																														///< does a shader already exist with that name

		static std::shared_ptr<Texture> addTexture(const std::string& filepath);																										///< add a Texture to the asset manager
		static std::shared_ptr<Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData);					///< add a Texture to the asset manager
		static std::shared_ptr<Texture> getTexture(const std::string& filepath);																										///< get a Texture from the asset manager
		static bool doesTextureExist(const std::string& filepath);																														///< does a Texture already exist with that name

		static std::shared_ptr<VertexArray> addVertexArray(const std::string& name);																									///< add a vertex buffer to the asset manager
		static std::shared_ptr<VertexArray> getVertexArray(const std::string& name);																									///< get a vertex buffer from the asset manager
		static bool doesVertexArrayExist(const std::string& name);																														///< does a vertex buffer already exist with that name

		static std::shared_ptr<VertexBuffer> addVertexBuffer(const std::string& name, float* vertices, unsigned int size, VertexBufferLayout& layout);									///< add a index buffer to the asset manager
		static std::shared_ptr<VertexBuffer> getVertexBuffer(const std::string& name);																									///< get a vertex buffer from the asset manager
		static bool doesVertexBufferExist(const std::string& name);																														///< does a vertex buffer already exist with that name

		static std::shared_ptr<Material> addMaterial(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> vertexArray);								///< add a material buffer to the asset manager
		static std::shared_ptr<Material> getMaterial(const std::string& name);																											///< get a material buffer from the asset manager
		static bool doesMaterialExist(const std::string& name);																															///< does a material buffer already exist with that name

		static std::shared_ptr<UniformBuffer> addUniformBuffer(const std::string& name, unsigned int size, UniformBufferLayout& layout);
		static std::shared_ptr<UniformBuffer> getUniformBuffer(const std::string& name);
		static bool doesUniformBufferExist(const std::string& name);

	};
}