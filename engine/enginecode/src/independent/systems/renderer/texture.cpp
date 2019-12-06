#include "engine_pch.h"
#include "systems/renderer/texture.h"
#include "systems/renderer/renderAPI.h"
#include "include/platform/OpenGL/OpenGL_texture.h"

namespace Engine
{
	Texture* Texture::createFromFile(const std::string& filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case API::None: return nullptr;
		case API::OpenGL: return new OpenGL_Texture(filepath);
		}
	}
	Texture* Texture::createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData)
	{
		switch (RenderAPI::getAPI())
		{
		case API::None: return nullptr;
		case API::OpenGL: return new OpenGL_Texture(width, height, channels, texData);
		}
	}
}
