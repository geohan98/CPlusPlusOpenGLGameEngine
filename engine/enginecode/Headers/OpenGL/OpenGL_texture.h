#pragma once
#include "../enginecode/Headers/renderer/texture.h"

namespace Engine
{
	namespace Renderer {
		/**
		 * GL Texture
		 */
		class OpenGL_Texture : public Texture
		{
		private:
			std::string m_filePath; ///< filepath of image
			unsigned int m_rendererID; ///< object id
			int m_width; ///< image width
			int m_height; ///< image height
			int m_channels; ///< number of channels
			unsigned int m_slot; ///< texture slot
			static unsigned int s_slot; ///< number of bound textures
		public:
			OpenGL_Texture(const std::string& filepath); ///< 
			OpenGL_Texture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData); ///< 
			~OpenGL_Texture(); ///< Decontrcutor
			inline unsigned int getWidth() const override { return m_width; }; ///< return the width of the texture
			inline unsigned int getHeight() const override { return m_height; }; ///< return the height of the texture

			unsigned int getChannels() const override { return m_channels; }; ///< return the number of channels for the texture
			unsigned int getSlot() const override; ///< return the texture slot 

			void bind(int slot) const override; ///< bind the texture
			void unbind() const override; ///< bind the texture
			virtual int getId() const override;
		};
	}
}