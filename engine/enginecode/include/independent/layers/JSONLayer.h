#pragma once
#include "layers/layer.h"
#include <memory>
#include <string>
#include <vector>

#include "core/gameObject.h"
#include "components/materialComponent.h"
#include "components/PositionComponent.h"
#include "components/velocityComponent.h"

namespace Engine
{
	class GameObject;
	class MaterialComponent;
	class PositionComponent;
	class VelocityComponent;
	//class ControllerComponent;
	class RenderCommand;

	class JSONLayer : public Layer
	{
	protected:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;
		std::vector<std::shared_ptr<PositionComponent>> m_positions;
		std::vector<std::shared_ptr<VelocityComponent>> m_velocities;
		//std::vector<std::shared_ptr<ControllerComponent>> m_controllers;

		std::vector<std::shared_ptr<RenderCommand>> m_initCommands;
		std::vector<std::shared_ptr<RenderCommand>> m_predrawCommands;
		std::vector<std::shared_ptr<RenderCommand>> m_postdrawCommands;
		std::vector<std::shared_ptr<RenderCommand>> m_exitCommands;

		SceneData m_sceneData;
		std::list<void*> m_data;
		std::string m_filepath;
	public:
		JSONLayer(const std::string& filepath, const std::string& name = "Layer") : Layer(name), m_filepath(filepath) {}

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(float deltaTime) override;
		virtual void onEvent(Event& e) override;

		inline std::vector<std::shared_ptr<GameObject>>& getGameObjects() { return m_gameObjects; }
		inline std::vector<std::shared_ptr<MaterialComponent>>& getMaterials() { return m_materials; }
		inline std::vector<std::shared_ptr<PositionComponent>>& getPositions() { return m_positions; }
		inline std::vector<std::shared_ptr<VelocityComponent>>& getVelocities() { return m_velocities; }
		//inline std::vector<std::shared_ptr<ControllerComponent>>& getControllers() { return m_controllers; }

		inline std::vector<std::shared_ptr<RenderCommand>>& getInitCommands() { return m_initCommands; }
		inline std::vector<std::shared_ptr<RenderCommand>>& getPredrawCommands() { return m_predrawCommands; }
		inline std::vector<std::shared_ptr<RenderCommand>>& getPostdrawCommands() { return m_postdrawCommands; }
		inline std::vector<std::shared_ptr<RenderCommand>>& getExitCommands() { return m_exitCommands; }

		inline std::list<void*>& getData() { return m_data; }
	};
}