#pragma once
#include "Headers/components/component.h"
//#include "Headers/systems/Physics.h"
#include "reactphysics3d.h"
#include "glm/glm.hpp"



namespace Engine {
	namespace Components {
		class PhysicsBoxComponent : public Component
		{
		private:
			rp3d::BoxShape* m_shape;
			rp3d::ProxyShape* m_proxy;
			rp3d::RigidBody* m_body;
		public:
			PhysicsBoxComponent(glm::vec3 Position, glm::vec4 Orientation, glm::vec3 boxSize, float density, bool useGravity = true);
			void onAttach(GameObject* parent) override { m_parent = parent; } ///< Run When Component is added to GameObject
			void onDetach() override; ///< Run When Component is Removed From Parent
			void onUpdate(float deltaTime) override; ///< Called Every Frame
			void onEvent(Events::Event& e) override; ///< Called on an Event
			void receiveMessage(const ComponentMessage& msg) override; ///< Receive a message from another component
			void enableGravity(bool isenabled); ///< Sets whether the ridgidbody uses gravity
			void addForce(glm::vec3 force, glm::vec3 point); ///< adds a force to the rigidbody
			void addTorque(glm::vec3 torque); ///< adds a torque to a ridgidbody
			void setAngularVelocity(glm::vec3 angularVelocity); ///< sets the angular velocity of the rigidbody
			void setLinearVelocity(glm::vec3 linearVelocity); ///< sets the velocity od the ridgidbody
		};

	}
}