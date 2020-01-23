#pragma once

namespace Engine
{
	namespace Renderer {
		/**
		 *  Index Buffer
		 */
		class IndexBuffer
		{
		public:
			virtual void bind() = 0;		///< Make this the active buffer
			virtual void unbind() = 0;		///< Make this not the active buffer

			virtual unsigned int getCount() const = 0; ///< Return the number of indices

			static IndexBuffer* create(unsigned int* indices, unsigned int count); ///< Create API Specific Object
		};
	}
}
