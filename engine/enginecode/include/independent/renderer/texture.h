#pragma once
#include <string>

namespace Engine
{
	/**
	 *  Texture
	 */
	class Texture
	{
	public:
		virtual unsigned int getWidth() const = 0;		///< Return the texture width
		virtual unsigned int getHeight() const = 0;		///< Return the texture height
		virtual unsigned int getChannels() const = 0;	///< Return the number of channels
		virtual unsigned int getSlot() const = 0;		///< Return the texture slot

		static Texture* createFromFile(const std::string& filepath); ///< Create API Specific Object
		static Texture* createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData); ///< Create API Specific Object

		virtual void bind() const = 0; ///< Make this the active texture
		virtual void unbind() const = 0; ///< Make this not the active texture
	};
}