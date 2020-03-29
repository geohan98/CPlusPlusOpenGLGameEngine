#pragma once
#include "Headers/layers/layer.h"
#include "worldGrid.h"
#include "Headers/renderer/model.h"
#include <memory>

namespace ParticleDesigner
{
	class ParticleLayer : public Engine::Layer
	{
	private:
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_predrawCommands;
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_postdrawCommands;
		std::shared_ptr<WorldGrid> m_worldGrid;
		std::shared_ptr<Engine::Model> m_debugCube;
	public:
		ParticleLayer(const std::string& name = "ParticleLayer") : Layer(name) {};
		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate(float deltaTime);
		virtual void onEvent(Engine::Events::Event& e);
	};
}