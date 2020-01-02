#pragma once
#include "core/layer.h"
#include "core/gameObject.h"
#include "components/materialComponent.h"
#include "components/PositionComponent.h"
#include "components/velocityComponent.h"

namespace Engine
{
	class GameLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;
		std::vector<std::shared_ptr<PositionComponent>> m_positions;
		std::vector<std::shared_ptr<VelocityComponent>> m_velocities;
		SceneData m_sceneData;
	public:
		GameLayer(const std::string& name = "Game Layer") : Layer(name) {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
	};
}