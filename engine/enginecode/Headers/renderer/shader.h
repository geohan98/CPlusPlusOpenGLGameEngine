#pragma once
#include <map>
#include <utility>

namespace Engine
{
	namespace Renderer {
		class VertexBufferLayout;
		using UniformLayout = std::map < std::string, void*>;
		/**
		 *  Shader
		 */
		class Shader
		{
		public:
			virtual ~Shader() {};

			virtual unsigned int getId() = 0;
			virtual void bind() = 0;		///< Make this the active shader
			virtual void unbind() = 0;		///< Make this not the active shader
			virtual bool uploadData(const std::string& name, void* data) = 0; ///< Set a single piece of data
			virtual VertexBufferLayout getBufferLayout() const = 0; ///< Return buffer layout
			virtual UniformLayout getUniformLayout() const = 0; ///< Return the uniform layout

			static Shader* create(const std::string& filepath); ///< Create API Specific Object
		};
	}
}