#pragma once
#include "renderer/renderer.h"

namespace Engine
{
	class OpenGL_BasicRenderer : public Renderer
	{
	private:
	public:
		void actionCommand(RenderCommand* command) override;
		void beginScene(const SceneData& sceneData) override;
		void endScene() override;
		void submit(const std::shared_ptr<Material>& materials) override;
		void flush() override;
	};
}