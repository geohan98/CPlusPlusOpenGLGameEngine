#pragma once
#include "systems/renderer/texture.h"

namespace Engine
{
	class OpenGL_Texture : public Texture
	{
	private:
		unsigned int id;
		OpenGL_Texture(const std::string & filepath);
		OpenGL_Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);

		unsigned int m_TextureSlot;
		static unsigned int s_TextureSlot;

		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_channels;

		unsigned char* m_LocalBuffer;
	public:
		unsigned int getWidth() const override;
		unsigned int getHeight() const override;
		unsigned int getChannels() const override;
		unsigned int getSlot() const override;
	};
}