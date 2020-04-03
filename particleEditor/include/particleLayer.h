#pragma once
#include "Headers/layers/layer.h"
#include "worldGrid.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/particleComponent.h"
#include <memory>

namespace ParticleDesigner
{
	class ParticleLayer : public Engine::Layer
	{
	private:
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_predrawCommands;
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_postdrawCommands;
		Engine::Renderer::SceneData m_sceneData;
		std::shared_ptr<WorldGrid> m_worldGrid;
		std::shared_ptr<Engine::GameObject> m_gameObject;
		std::shared_ptr<Engine::Components::ParticleComponent> m_particleComponent;
		std::shared_ptr<Engine::PositionComponent> m_positionComponent;
	public:
		ParticleLayer(const std::string& name = "ParticleLayer") : Layer(name) {};
		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate(float deltaTime);
		virtual void onEvent(Engine::Events::Event& e);
	};
}