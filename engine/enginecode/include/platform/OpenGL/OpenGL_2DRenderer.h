#pragma once
#include "renderer/renderer.h"

namespace Engine
{
	namespace Renderer {
		/**
		 * GL 2D Renderer
		 */
		class OpenGL_2DRenderer : public Renderer
		{
		private:
		public:
			void actionCommand(RenderCommand* command) override; ///< Action render command
			void beginScene(const SceneData& sceneData) override {}; ///< Not Implemented
			void endScene() override {}; ///< ///< Not Implemented
			void submit(const std::shared_ptr<Material>& materials) override; ///< submit a materail for rendering
			void flush() override {}; ///< ///< Not Implemented
		};
	}
}