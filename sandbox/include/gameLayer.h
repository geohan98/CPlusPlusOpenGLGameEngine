#pragma once
#include "../enginecode/Headers/layers/layer.h"
#include "../enginecode/Headers/core/gameObject.h"
#include "../enginecode/Headers/renderer/uniformBuffer.h"
#include "Headers/components/particleComponent.h"


namespace Engine
{
	/**
	 *  Game Layer, Handles Game objects
	 */
	class GameLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;					///< All the GameObjects
		std::vector<std::shared_ptr<Components::ParticleComponent>> m_particleComponents;
		Renderer::SceneData m_sceneData;
		glm::vec3 colour = glm::vec3(0.5f);
	public:
		GameLayer(const std::string& name = "Game Layer") : Layer(name) {};		///< Constructor
		void onAttach() override;												///< Run on layer Attach
		void onDetach() override;												///< Run on Layer remove from layer stack
		void onUpdate(float deltaTime) override;								///< Run every Frame
		void onEvent(Events::Event& e) override;								///< Run on an Event
	};
}