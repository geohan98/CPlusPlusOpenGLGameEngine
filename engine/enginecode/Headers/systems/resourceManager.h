#pragma once
#include "system.h"
#include "Headers/assetManager.h"
#include "Headers/renderer/indexBuffer.h"
#include "Headers/renderer/shader.h"
#include "Headers/renderer/texture.h"
#include "Headers/renderer/vertexBuffer.h"
#include "Headers/renderer/vertexBufferLayout.h"
#include "Headers/renderer/vertexArray.h"
#include "Headers/renderer/material.h"
#include "Headers/renderer/uniformBuffer.h"
#include "Headers/textRendering/character.h"

namespace Engine
{
	namespace Systems {
		/**
		 * Resource Manger, Handles resources for the engine
		 */
		class ResourceManager : public System
		{
		private:
			static AssetManager<Renderer::IndexBuffer> m_indexBuffersObjects;																															///< Index Buffer Asset Manager
			static AssetManager<Renderer::Shader> m_shaders;																																			///< Shader Asset Manager
			static AssetManager<Renderer::Texture> m_textures;																																		///< Texture Asset Manager
			static AssetManager<Renderer::VertexArray> m_vertexArrayObjects;																															///< Vertex Array Asset Manager
			static AssetManager<Renderer::VertexBuffer> m_vertexBufferObjects;																														///< Vertex Buffer Asset Manager
			static AssetManager<Renderer::Material> m_materials;																																		///< Material Asset Manager
			static AssetManager<Renderer::UniformBuffer> m_uniformBuffers;

			static std::map<std::string, std::vector<Character>> m_characters; //Font Characters
			static const int m_ASCIIstart = 32;
			static const int m_ASCIIend = 126;
			static std::shared_ptr<Renderer::Texture> m_fontTexture;

			static std::string parseFilePath(const std::string& str);																														///< Remove all but the file name
		public:
			void start(SystemSignal init = SystemSignal::None, ...) override;																												///< Start the Resource Manager
			void stop(SystemSignal close = SystemSignal::None, ...) override;																												///< Stop the Resource Manager

			static std::shared_ptr<Renderer::IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);															///< add a index buffer to the asset manager
			static std::shared_ptr<Renderer::IndexBuffer> getIndexBuffer(const std::string& name);																									///< get a index buffer from the asset manager
			static bool doesIndexBufferExist(const std::string& name);																														///< does a index buffer already exist with that name

			static std::shared_ptr<Renderer::Shader> addShader(const std::string& filepath);																											///< add a shader to the asset manager
			static std::shared_ptr<Renderer::Shader> getShader(const std::string& filepath);																											///< get a shader from the asset manager
			static bool doesShaderExist(const std::string& filepath);																														///< does a shader already exist with that name

			static std::shared_ptr<Renderer::Texture> addTexture(const std::string& filepath);																										///< add a Texture to the asset manager
			static std::shared_ptr<Renderer::Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData);					///< add a Texture to the asset manager
			static std::shared_ptr<Renderer::Texture> getTexture(const std::string& filepath);																										///< get a Texture from the asset manager
			static bool doesTextureExist(const std::string& filepath);																														///< does a Texture already exist with that name

			static std::shared_ptr<Renderer::VertexArray> addVertexArray(const std::string& name);																									///< add a vertex buffer to the asset manager
			static std::shared_ptr<Renderer::VertexArray> getVertexArray(const std::string& name);																									///< get a vertex buffer from the asset manager
			static bool doesVertexArrayExist(const std::string& name);																														///< does a vertex buffer already exist with that name

			static std::shared_ptr<Renderer::VertexBuffer> addVertexBuffer(const std::string& name, float* vertices, unsigned int size, Renderer::VertexBufferLayout& layout);									///< add a index buffer to the asset manager
			static std::shared_ptr<Renderer::VertexBuffer> getVertexBuffer(const std::string& name);																									///< get a vertex buffer from the asset manager
			static bool doesVertexBufferExist(const std::string& name);																														///< does a vertex buffer already exist with that name

			static std::shared_ptr<Renderer::Material> addMaterial(const std::string& name, std::shared_ptr<Renderer::Shader> shader, std::shared_ptr<Renderer::VertexArray> vertexArray);								///< add a material buffer to the asset manager
			static std::shared_ptr<Renderer::Material> getMaterial(const std::string& name);																											///< get a material buffer from the asset manager
			static bool doesMaterialExist(const std::string& name);																															///< does a material buffer already exist with that name

			static std::shared_ptr<Renderer::UniformBuffer> addUniformBuffer(const std::string& name, unsigned int size, Renderer::UniformBufferLayout& layout);
			static std::shared_ptr<Renderer::UniformBuffer> getUniformBuffer(const std::string& name);
			static bool doesUniformBufferExist(const std::string& name);

			static void populateCharacters(std::unordered_map<std::string, unsigned int> _fontAndSizes);
			static std::shared_ptr<Character> getCharacter(std::string _font, unsigned int _ASCIIcode);
			inline static std::shared_ptr<Renderer::Texture> getFontTexture() { return m_fontTexture; };

		};
	}
}