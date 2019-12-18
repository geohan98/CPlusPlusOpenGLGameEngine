
#include <memory>

#include "systems/renderer/renderCommand.h"
#include "systems/renderer/material.h"
#include "systems/renderer/uniformBuffer.h"

namespace Engine
{
	using SceneData = std::unordered_map<std::shared_ptr<UniformBuffer>, std::vector<void*>>;
	using PerDrawData = std::map<std::string, void*>;

	class Renderer
	{
	public:
		virtual void actionCommand(RenderCommand* command) = 0;
		virtual void beginScene(const SceneData& sceneData) = 0;
		virtual void endScene() = 0;
		virtual void submit(const std::shared_ptr<Material>& materials) = 0;
		virtual void flush() = 0;

		static Renderer* createBasic3D();
	};
}