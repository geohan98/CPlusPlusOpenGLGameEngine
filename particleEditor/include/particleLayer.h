#pragma once
#include "Headers/layers/layer.h"
#include "worldGrid.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/particleComponent.h"
#include <memory>
#include "msgTypes.h"

namespace ParticleEditor
{
	class ParticleLayer : public Engine::Layer
	{
	private:
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_predrawCommands; ///< Commands to be execute before every draw
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_postdrawCommands; ///< Commands to be executed after every draw
		Engine::Renderer::SceneData m_sceneData; ///< Data About Scene for UBO
		std::shared_ptr<WorldGrid> m_worldGrid; ///< The world grid, used for mesaureing and a sense of scale
		std::shared_ptr<Engine::GameObject> m_gameObject; ///< The gameobject for the particle system
		std::shared_ptr<Engine::Components::ParticleComponent> m_particleComponent; ///< The particle system
		std::shared_ptr<Engine::PositionComponent> m_positionComponent; ///< The postion of the particle system
	public:
		ParticleLayer(const std::string& name = "ParticleLayer") : Layer(name) {}; ///< Constructior
		virtual void onAttach(); ///< Runs on layer attach to layer stack
		virtual void onDetach();///< Runs on layer remove to layer stack
		virtual void onUpdate(float deltaTime); ///< Runs on Every Frame
		virtual void onEvent(Engine::Events::Event& e); ///< Runs on Event passed from application
	public:
		void beNotified(MsgType _type, std::any _data) override ///< Part of observer pattern, updates the particle system proerties
		{
			if (_type == UPDATE_PARTICLE_SYSTEM)
			{
				Engine::ParticleSystemProperties* properties = std::any_cast<Engine::ParticleSystemProperties*>(_data);
				m_particleComponent->reset(properties);
			}
		};
	};
}