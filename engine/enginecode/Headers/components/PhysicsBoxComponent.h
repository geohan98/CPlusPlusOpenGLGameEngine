#pragma once
#include "Headers/components/component.h"
//#include "Headers/systems/Physics.h"
#include "reactphysics3d.h"
#include "glm/glm.hpp"



namespace Engine {

	class PhysicsBoxComponent : public Component
	{
	private:
		rp3d::BoxShape* m_shape;
		rp3d::ProxyShape* m_proxy;
		rp3d::RigidBody* m_body;
	public:
		PhysicsBoxComponent(glm::vec3 Position, glm::vec4 Orientation, glm::vec3 boxSize, float density);
		void onAttach(GameObject* parent) override { m_parent = parent; } ///< Run When Component is added to GameObject
		void onDetach() override; ///< Run When Component is Removed From Parent
		void onUpdate(float deltaTime) override; ///< Called Every Frame
		void onEvent(Events::Event& e) override; ///< Called on an Event
		void receiveMessage(const ComponentMessage& msg) override; ///< Receive a message from another component

	};


}