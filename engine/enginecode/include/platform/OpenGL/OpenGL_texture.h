#pragma once
#include "renderer/texture.h"

namespace Engine
{
	class OpenGL_Texture : public Texture
	{
	private:
		std::string m_filePath;
		unsigned int m_id;
		int m_width;
		int m_height;
		int m_channels;
		unsigned int m_slot;
		static unsigned int s_slot;
	public:
		OpenGL_Texture(const std::string& filepath);
		OpenGL_Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData);
		~OpenGL_Texture();

		inline unsigned int getWidth() const override { return m_width; };
		inline unsigned int getHeight() const override { return m_height; };

		unsigned int getChannels() const override { return m_channels; };
		unsigned int getSlot() const override;

		void bind() const;
		void unbind() const;
	};
}