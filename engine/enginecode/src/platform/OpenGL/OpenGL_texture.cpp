#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_texture.h"
#include "glad/glad.h"

namespace Engine
{
	OpenGL_Texture::OpenGL_Texture(const std::string & filepath)
	{
		glGenTextures(1, &id);
		m_TextureSlot = s_TextureSlot;
		s_TextureSlot++;
		glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	OpenGL_Texture::OpenGL_Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{

	}

	unsigned int OpenGL_Texture::getWidth() const
	{
		return m_width;
	}

	unsigned int OpenGL_Texture::getHeight() const
	{
		return m_height;
	}

	unsigned int OpenGL_Texture::getChannels() const
	{
		return m_channels;
	}

	unsigned int OpenGL_Texture::getSlot() const
	{
		return m_TextureSlot;
	}

	Texture * Engine::Texture::createFromFile(const std::string & filepath)
	{
		return new OpenGL_Texture(filepath);
	}

	Texture * Engine::Texture::createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		return new OpenGL_Texture(width,height,channels, texData);
	}
}