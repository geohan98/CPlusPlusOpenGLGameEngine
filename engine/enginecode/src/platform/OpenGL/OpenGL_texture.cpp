#include "engine_pch.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_texture.h"
#include "glad/glad.h"
#include <stb_image.h>

namespace Engine
{
	OpenGL_Texture::OpenGL_Texture(const std::string& filepath) : m_id(0), m_filePath(filepath), m_width(0), m_height(0), m_channels(0)
	{
		stbi_set_flip_vertically_on_load(1);
		unsigned char* localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_channels, 4);
		if (!localBuffer)
		{
			LOG_CORE_ERROR("UNABLE TO LOAD TEXTURE {0}", m_filePath.c_str());
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

		glTexParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (m_channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			glTexImage2D(m_id, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		else if (m_channels == 4)
		{
			glTexImage2D(m_id, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		}
		else if (m_channels == 1)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(m_id, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, localBuffer);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		glGenerateMipmap(m_id);

		if (localBuffer)
		{
			stbi_image_free(localBuffer);
		}


	}

	OpenGL_Texture::OpenGL_Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData) : m_id(0), m_filePath(""), m_width(0), m_height(0), m_channels(0)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

		glTextureStorage2D(m_id, 1, GL_RGBA, m_width, m_height);

		glTexParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			glTexImage2D(m_id, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		else if (channels == 4)
		{
			glTexImage2D(m_id, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		}
		else if (channels == 1)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(m_id, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		glGenerateMipmap(m_id);
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
		glBindTextureUnit(slot, m_id);
	}

	void OpenGL_Texture::unbind() const
	{
		LOG_CORE_INFO("NO TEXTURE UNBIND FUNCTION SET");
	}
}