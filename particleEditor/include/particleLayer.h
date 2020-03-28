#pragma once
#include "Headers/layers/layer.h"
#include <memory>
#include "worldGrid.h"

namespace ParticleDesigner
{
	class ParticleLayer : public Engine::Layer
	{
	private:
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_predrawCommands;
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_postdrawCommands;
		std::shared_ptr<WorldGrid> m_worldGrid;
	public:
		ParticleLayer(const std::string& name = "ParticleLayer") : Layer(name) {};
		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate(float deltaTime);
		virtual void onEvent(Engine::Events::Event& e);
	};
}