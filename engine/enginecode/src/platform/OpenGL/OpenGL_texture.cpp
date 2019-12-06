#include "engine_pch.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_texture.h"
#include "glad/glad.h"
#include <stb_image.h>

namespace Engine
{
	unsigned int OpenGL_Texture::s_slot = 0;

	OpenGL_Texture::OpenGL_Texture(const std::string& filepath) : m_id(0), m_filePath(filepath), m_width(0), m_height(0), m_channels(0)
	{
		stbi_set_flip_vertically_on_load(1);
		unsigned char* localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_channels, 0);
		if (!localBuffer)
		{
			LOG_CORE_ERROR("UNABLE TO LOAD TEXTURE {0}", m_filePath.c_str());
		}

		glGenTextures(1, &m_id);
		m_slot = s_slot;
		s_slot++;
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (m_channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
		}
		else if (m_channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		}
		else if (m_channels == 1)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, localBuffer);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		glGenerateMipmap(GL_TEXTURE_2D);


		if (localBuffer)
		{
			stbi_image_free(localBuffer);
		}

	}

	OpenGL_Texture::~OpenGL_Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	unsigned int OpenGL_Texture::getSlot() const
	{
		return 0;
	}

	void OpenGL_Texture::bind() const
	{
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void OpenGL_Texture::unbind() const
	{
		LOG_CORE_INFO("NO TEXTURE UNBIND FUNCTION SET");
	}
}