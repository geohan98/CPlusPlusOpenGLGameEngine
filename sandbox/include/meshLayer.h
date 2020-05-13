#pragma once

#include "Headers/layers/layer.h"
#include "worldGrid.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/ModelComponent.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/PhysicsBoxComponent.h"

namespace Engine
{
	class MeshLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_predrawCommands; ///< Commands to be execute before every draw
		std::vector<std::shared_ptr<Engine::Renderer::RenderCommand>> m_postdrawCommands; ///< Commands to be executed after every draw
		std::shared_ptr<WorldGrid> m_worldGrid;
	private:
		//Cube
		std::shared_ptr<GameObject> m_cube;
		std::shared_ptr<Components::ModelComponent> m_cubeModelComponent;
		std::shared_ptr<PositionComponent> m_cubePositionComponent;
		std::shared_ptr<PhysicsBoxComponent> m_cubePhysicsBoxComponent;
		//Plane
		std::shared_ptr<GameObject> m_plane;
		std::shared_ptr<Components::ModelComponent> m_planeModelComponent;
		std::shared_ptr<PositionComponent> m_planePositionComponent;
		std::shared_ptr<PhysicsBoxComponent> m_planePhysicsBoxComponent;
	public:
		MeshLayer(const std::string& name = "Game Layer") : Layer(name) {};
		~MeshLayer() {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float deltaTime) override;
		void onEvent(Events::Event& e) override;
	};
}