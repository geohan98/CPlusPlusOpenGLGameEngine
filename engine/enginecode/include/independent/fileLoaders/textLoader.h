#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "systems/resourceManager.h"
#include "systems/log.h"

namespace Engine
{
	class TextModel
	{
	public:
		TextModel() : vertices(nullptr), indices(nullptr), verticesSize(0), indicesSize(0), shader(nullptr), texture(nullptr) {}
		~TextModel()
		{

		}
		float* vertices;
		unsigned int* indices;
		unsigned int verticesSize;
		unsigned int indicesSize;
		std::shared_ptr<Renderer::Shader> shader;
		std::shared_ptr<Renderer::Texture> texture;
	};

	class TextLoader
	{
	public:
		static bool loadModel(std::shared_ptr<Systems::ResourceManager> res, const std::string& filepath, TextModel& model)
		{
#ifdef NG_DEBUG
			LOG_CORE_INFO("MODEL LOADER: LOADING MODEL '{0}'", filepath);
#endif // NG_DEBUG
			std::fstream handle(filepath, std::ios::in);
			if (!handle.is_open()) return false;

			std::string line;
			std::stringstream ss;

			// Read vertex size
			getline(handle, line);
			ss.str(line);
			if (!ss.eof())
			{
				ss >> model.verticesSize;
				if (model.verticesSize <= 0) return false;
			}
			else return false;

			// Set up vertex array
			model.vertices = new float[model.verticesSize];
#ifdef NG_DEBUG
			LOG_CORE_INFO("MODEL LOADER: NUMBER OF VERTS '{0}'", model.verticesSize);
#endif // NG_DEBUG

			// read vertex data
			getline(handle, line);
			float value;

			ss.clear();
			ss.str(line);
			int i = 0;
			while (!ss.eof())
			{
				ss >> value;
				model.vertices[i] = value;
				i++;
			}

			// Read indices size
			getline(handle, line);
			ss.clear();
			ss.str(line);
			if (!ss.eof())
			{
				ss >> model.indicesSize;
				if (model.indicesSize <= 0) return false;
			}
			else
			{
				return false;
			}

			// Set up array
			model.indices = new unsigned int[model.indicesSize];
#ifdef NG_DEBUG
			LOG_CORE_INFO("MODEL LOADER: NUMBER OF INDICES '{0}'", model.indicesSize);
#endif // NG_DEBUG

			// read data
			getline(handle, line);
			unsigned int value2;

			ss.clear();
			ss.str(line);
			i = 0;
			while (!ss.eof())
			{
				ss >> value2;
				model.indices[i] = value2;
				i++;
			}

			// read Shader
			getline(handle, line);
			if (line.compare("NULL") != 0)
			{
				model.shader = res->addShader(line);
#ifdef NG_DEBUG
				LOG_CORE_INFO("MODEL LOADER: USING SHADER '{0}'", line);
#endif // NG_DEBUG
			}
			else model.texture = nullptr;

			// read texture
			getline(handle, line);
			if (line.compare("NULL") != 0)
			{
				model.texture = res->addTexture(line);
#ifdef NG_DEBUG
				LOG_CORE_INFO("MODEL LOADER: USING TEXTURE '{0}'", line);
#endif // NG_DEBUG
			}
			else model.texture = nullptr;
#ifdef NG_DEBUG
			LOG_CORE_INFO("MODEL LOADER: SUCCESSFULLY LOADED MODEL '{0}'", filepath);
#endif // NG_DEBUG
		}
	};
}