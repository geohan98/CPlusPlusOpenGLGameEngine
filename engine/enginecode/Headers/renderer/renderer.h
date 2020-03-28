#pragma once
#include <memory>
#include "../enginecode/Headers/renderer/renderCommand.h"
#include "../enginecode/Headers/renderer/material.h"
#include "../enginecode/Headers/renderer/uniformBuffer.h"

namespace Engine
{


	namespace Renderer {

		enum RendererDrawType
		{
			Triangle = 0,
			Quad,
			Lines,
			Point
		};

		using SceneData = std::unordered_map<std::shared_ptr<UniformBuffer>, std::vector<void*>>;
		using PerDrawData = std::map<std::string, void*>;
		/**
		 *  Renderer
		 */
		class Renderer
		{
		public:
			virtual void actionCommand(RenderCommand* command) = 0; ///< Action a render command
			virtual void beginScene(const SceneData& sceneData) = 0; ///< Begin Scene, apply scene data
			virtual void endScene() = 0; ///< End Scene Clean Up
			virtual void submit(const std::shared_ptr<Material>& materials, RendererDrawType _drawType = RendererDrawType::Triangle) = 0; ///< Submit a material to be rendered
			virtual void flush() = 0; ///< Not Implemented, used for bath rendering

			static Renderer* createBasic3D(); ///< Create API Specific 3D Renderer
			static Renderer* createBasic2D(); ///< Create API Specific 2D Renderer
		};

	}
}