#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_texture.h"
#include "glad/glad.h"

namespace Engine
{
	OpenGL_Texture::OpenGL_Texture(const std::string& filepath)
	{
		glGenTextures(1, &m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	OpenGL_Texture::OpenGL_Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData) : m_width(width), m_height(height), m_channels(channels)
	{
		glGenTextures(1, &m_id);
		glTextureStorage2D(m_id, 1, GL_RGBA, m_width, m_height);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		else if (channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		}
		else if (channels == 1)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGL_Texture::~OpenGL_Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	unsigned int OpenGL_Texture::getSlot() const
	{
		return 0;
	}
	void OpenGL_Texture::bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
	void OpenGL_Texture::unbind() const
	{
	}
}