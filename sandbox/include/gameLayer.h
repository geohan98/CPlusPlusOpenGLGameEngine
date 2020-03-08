#pragma once
#include "../enginecode/Headers/layers/layer.h"
#include "../enginecode/Headers/core/gameObject.h"
#include "../enginecode/Headers/renderer/uniformBuffer.h"
#include "Headers/components/particleComponent.h"
#include "Headers/components/PositionComponent.h"



namespace Engine
{
	/**
	 *  Game Layer, Handles Game objects
	 */
	class GameLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;					///< All the GameObjects
		std::vector<std::shared_ptr<PositionComponent>> m_positionComponents;
		std::vector<std::shared_ptr<Components::ParticleComponent>> m_particleComponents;
		Renderer::SceneData m_sceneData;

		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_predrawCommands;	///< List of all PreDraw Render Commands
		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_postdrawCommands;	///< List of all PostDraw Render Commands
	public:
		GameLayer(const std::string& name = "Game Layer") : Layer(name) {};		///< Constructor
		void onAttach() override;												///< Run on layer Attach
		void onDetach() override;												///< Run on Layer remove from layer stack
		void onUpdate(float deltaTime) override;								///< Run every Frame
		void onEvent(Events::Event& e) override;								///< Run on an Event
	};
}