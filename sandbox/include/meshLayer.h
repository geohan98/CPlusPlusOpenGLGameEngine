#pragma once

#include "Headers/layers/layer.h"
#include "worldGrid.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/ModelComponent.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/PhysicsBoxComponent.h"
#include "Headers/components/PhysicsSphereComponent.h"

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
		std::shared_ptr<Components::PositionComponent> m_cubePositionComponent;
		std::shared_ptr<Components::PhysicsBoxComponent> m_cubePhysicsBoxComponent;
		//Plane
		std::shared_ptr<GameObject> m_plane;
		std::shared_ptr<Components::ModelComponent> m_planeModelComponent;
		std::shared_ptr<Components::PositionComponent> m_planePositionComponent;
		std::shared_ptr<Components::PhysicsBoxComponent> m_planePhysicsBoxComponent;
		//Sphere
		std::shared_ptr<GameObject> m_sphere;
		std::shared_ptr<Components::ModelComponent> m_sphereModelComponent;
		std::shared_ptr<Components::PositionComponent> m_spherePositionComponent;
		std::shared_ptr<Components::PhysicsSphereComponent> m_spherePhysicsSphereComponent;
	public:
		MeshLayer(const std::string& name = "Game Layer") : Layer(name) {};
		~MeshLayer() {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float deltaTime) override;
		void onEvent(Events::Event& e) override;
		void beNotified(MsgType _type, std::any _data) override ///< Part of observer pattern, updates the particle system proerties
		{
			if (_type == 0)
			{
				glm::vec3 force = std::any_cast<glm::vec3>(_data);
				m_cubePhysicsBoxComponent->addForce(force);
			}
			if (_type == 1)
			{
				m_cubePhysicsBoxComponent->setPosition(glm::vec3(-2.0, 2.0, 0.0));
				m_cubePhysicsBoxComponent->setLinearVelocity(glm::vec3(0, 0.1, 0));
				m_cubePhysicsBoxComponent->setAngularVelocity(glm::vec3(0, 0.1, 0));
				m_spherePhysicsSphereComponent->setPosition(glm::vec3(2.0, 2.0, 0.0));
				m_spherePhysicsSphereComponent->setLinearVelocity(glm::vec3(0, 0.1, 0));
				m_spherePhysicsSphereComponent->setAngularVelocity(glm::vec3(0, 0.1, 0));
			}
		};
	};
}