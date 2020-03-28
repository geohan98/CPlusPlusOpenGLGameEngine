#pragma once
#include "../enginecode/Headers/renderer/renderer.h"

namespace Engine
{
	namespace Renderer {
		/**
		 *  GL 3D Renderer
		 */
		class OpenGL_BasicRenderer : public Renderer
		{
		private:
		public:
			void actionCommand(RenderCommand* command) override; ///< Action A render command
			void beginScene(const SceneData& sceneData) override; ///< Apply Uniform Data
			void endScene() override; ///< Cleanup the scene
			void submit(const std::shared_ptr<Material>& materials, RendererDrawType _drawType) override; ///< Submit a material fo rendering
			void flush() override; ///< ///< Not Implemented
		};
	}
}