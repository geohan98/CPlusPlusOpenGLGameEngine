#pragma once
#include <string>

namespace Engine
{
	class Texture
	{
	public:
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getChannels() const = 0;
		virtual unsigned int getSlot() const = 0;

		static Texture* createFromFile(const std::string& filepath);
		static Texture* createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData);

		virtual void bind(unsigned int = 0) const = 0;
		virtual void unbind() const = 0;
	};
}