#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "Headers/systems/resourceManager.h"
#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Engine
{
	namespace Systems {
		AssetManager<Renderer::IndexBuffer> ResourceManager::m_indexBuffersObjects;
		AssetManager<Renderer::Shader> ResourceManager::m_shaders;
		AssetManager<Renderer::Texture> ResourceManager::m_textures;
		AssetManager<Renderer::VertexArray> ResourceManager::m_vertexArrayObjects;
		AssetManager<Renderer::VertexBuffer> ResourceManager::m_vertexBufferObjects;
		AssetManager<Renderer::Material> ResourceManager::m_materials;
		AssetManager<Renderer::UniformBuffer> ResourceManager::m_uniformBuffers;

		std::map<std::string, std::vector<Character>> ResourceManager::m_characters;
		const int ResourceManager::m_ASCIIstart;
		const int ResourceManager::m_ASCIIend;
		std::shared_ptr<Renderer::Texture> ResourceManager::m_fontTexture;

		std::string ResourceManager::parseFilePath(const std::string& str)
		{
			std::string x = str;
			x = x.substr(x.find_last_of("/") + 1);
			x = x.erase(x.find("."));
			return x;
		}

		void ResourceManager::start(SystemSignal init, ...)
		{
			LOG_CORE_WARN("[SYSTEMS][RESOURCE MANAGER][RESOURCE MANAGER STARTED]");
		}

		void ResourceManager::stop(SystemSignal close, ...)
		{
			LOG_CORE_WARN("[SYSTEMS][RESOURCE MANAGER][RESOURCE MANAGER STOPPED]");
		}

		//INDEX BUFFERS

		std::shared_ptr<Renderer::IndexBuffer> ResourceManager::addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count)
		{
			m_indexBuffersObjects.add(name, std::shared_ptr<Renderer::IndexBuffer>(Renderer::IndexBuffer::create(indices, count)));
			return m_indexBuffersObjects.get(name);
		}

		std::shared_ptr<Renderer::IndexBuffer> ResourceManager::getIndexBuffer(const std::string& name)
		{
			return m_indexBuffersObjects.get(name);
		}

		bool ResourceManager::doesIndexBufferExist(const std::string& name)
		{
			return m_indexBuffersObjects.contains(name);
		}

		//SHADERS

		std::shared_ptr<Renderer::Shader> ResourceManager::addShader(const std::string& filepath)
		{
			m_shaders.add(parseFilePath(filepath), std::shared_ptr<Renderer::Shader>(Renderer::Shader::create(filepath)));
			return m_shaders.get(parseFilePath(filepath));
		}

		std::shared_ptr<Renderer::Shader> ResourceManager::getShader(const std::string& filepath)
		{
			return m_shaders.get(parseFilePath(filepath));;
		}

		bool ResourceManager::doesShaderExist(const std::string& filepath)
		{
			return m_shaders.contains(filepath);
		}

		//TEXTURES

		std::shared_ptr<Renderer::Texture> ResourceManager::addTexture(const std::string& filepath)
		{
			m_textures.add(parseFilePath(filepath), std::shared_ptr<Renderer::Texture>(Renderer::Texture::createFromFile(filepath)));
			return m_textures.get(parseFilePath(filepath));
		}

		std::shared_ptr<Renderer::Texture> ResourceManager::addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData)
		{
			m_textures.add(name, std::shared_ptr<Renderer::Texture>(Renderer::Texture::createFromRawData(width, height, channels, texData)));
			return m_textures.get(name);
		}

		std::shared_ptr<Renderer::Texture> ResourceManager::getTexture(const std::string& filepath)
		{
			return m_textures.get(parseFilePath(filepath));
		}

		bool ResourceManager::doesTextureExist(const std::string& filepath)
		{
			return m_textures.contains(filepath);
		}

		//VERTEX ARRAYS

		std::shared_ptr<Renderer::VertexArray> ResourceManager::addVertexArray(const std::string& name)
		{
			m_vertexArrayObjects.add(name, std::shared_ptr<Renderer::VertexArray>(Renderer::VertexArray::create()));
			return m_vertexArrayObjects.get(name);
		}

		std::shared_ptr<Engine::Renderer::VertexArray> ResourceManager::getVertexArray(const std::string& name)
		{
			return m_vertexArrayObjects.get(name);
		}

		bool ResourceManager::doesVertexArrayExist(const std::string& name)
		{
			return m_vertexArrayObjects.contains(name);
		}

		//VERTEX BUFFERS

		std::shared_ptr<Engine::Renderer::VertexBuffer> ResourceManager::addVertexBuffer(const std::string& name, float* vertices, unsigned int size, Renderer::VertexBufferLayout& layout)
		{
			m_vertexBufferObjects.add(name, std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(vertices, size, layout)));
			return m_vertexBufferObjects.get(name);
		}

		std::shared_ptr<Engine::Renderer::VertexBuffer> ResourceManager::getVertexBuffer(const std::string& name)
		{
			return m_vertexBufferObjects.get(name);
		}

		bool ResourceManager::doesVertexBufferExist(const std::string& name)
		{
			return m_vertexBufferObjects.contains(name);
		}

		//MATERIALS

		std::shared_ptr<Renderer::Material> ResourceManager::addMaterial(const std::string& name, std::shared_ptr<Renderer::Shader> shader, std::shared_ptr<Renderer::VertexArray> vertexArray)
		{
			m_materials.add(name, std::shared_ptr<Renderer::Material>(Renderer::Material::create(shader, vertexArray)));
			return m_materials.get(name);
		}

		std::shared_ptr<Renderer::Material> ResourceManager::getMaterial(const std::string& name)
		{
			return m_materials.get(name);
		}

		bool ResourceManager::doesMaterialExist(const std::string& name)
		{
			return m_materials.contains(name);
		}

		std::shared_ptr<Engine::Renderer::UniformBuffer> ResourceManager::addUniformBuffer(const std::string& name, unsigned int size, Renderer::UniformBufferLayout& layout)
		{
			m_uniformBuffers.add(name, std::shared_ptr<Renderer::UniformBuffer>(Renderer::UniformBuffer::create(size, layout)));
			return m_uniformBuffers.get(name);
		}

		std::shared_ptr<Engine::Renderer::UniformBuffer> ResourceManager::getUniformBuffer(const std::string& name)
		{
			return m_uniformBuffers.get(name);
		}

		bool ResourceManager::doesUniformBufferExist(const std::string& name)
		{
			return m_uniformBuffers.contains(name);
		}

		//FONTS

		void ResourceManager::populateCharacters(std::unordered_map<std::string, unsigned int> _fontAndSizes)
		{
			//Mem Setup
			unsigned char* texMemory;
			int memH = 1024;
			int memW = 1024;
			texMemory = (unsigned char*)malloc(memW * memH);
			memset(texMemory, 0, memW * memH);

			FT_Library ft;
			FT_Face face;

			if (FT_Init_FreeType(&ft)) LOG_CORE_CRITICAL("[RESOURCE MANAGER][FONTS][COULD NOT START FREETYPE]");

			for each (std::pair<std::string, unsigned int> font in _fontAndSizes)
			{
				glm::ivec2 maxSize = glm::ivec2(0);
				std::pair<std::string, std::vector<Character>> fontChars;

				if (FT_New_Face(ft, font.first.c_str(), 0, &face)) LOG_CORE_CRITICAL("[RESOURCE MANAGER][FONTS][FREETYPE COULD NOT LOAD FONT {0}]", font.first);
				if (FT_Set_Pixel_Sizes(face, 0, font.second)) LOG_CORE_CRITICAL("[RESOURCE MANAGER][FONTS][FREETYPE COULD NOT SET FONT FACE SIZE OF {0}]", font.second);

				fontChars.first = font.first;

				for (int i = m_ASCIIstart; i < m_ASCIIend; i++)
				{
					if (FT_Load_Char(face, i, FT_LOAD_RENDER))LOG_CORE_CRITICAL("[RESOURCE MANAGER][FONTS][COULD NOT LOAD THE CHARACTER {0}]", (char)i);
					if (face->glyph->bitmap.width > maxSize.x) maxSize.x = face->glyph->bitmap.width;
					if (face->glyph->bitmap.rows > maxSize.y) maxSize.y = face->glyph->bitmap.rows;
					fontChars.second.push_back(Character(glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x));
				}
				int start = 0;
				for (int i = m_ASCIIstart; i < m_ASCIIend; i++)
				{
					if (FT_Load_Char(face, i, FT_LOAD_RENDER))LOG_CORE_CRITICAL("[RESOURCE MANAGER][FONTS][COULD NOT LOAD THE CHARACTER {0}]", (char)i);

					int rows = face->glyph->bitmap.rows;
					int columns = face->glyph->bitmap.width;

					for (int j = 0; j < rows; j++)
					{
						for (size_t k = 0; k < columns; k++)
						{
							int offset = j * 1024 + k + start;

							int glyphOffset = j * columns + k;

							*(texMemory + offset) = *(face->glyph->bitmap.buffer + glyphOffset);
						}

					}
				}

				m_characters.emplace(fontChars);
			}
		}

		std::shared_ptr<Character> ResourceManager::getCharacter(std::string _font, unsigned int _ASCIIcode)
		{
			return std::shared_ptr<Character>();
		}

	}
}