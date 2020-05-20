#pragma once
#include "Headers/components/component.h"
#include "reactphysics3d.h"
#include "glm/glm.hpp"

namespace Engine {
	namespace Components {
		/**
	 *  Physics Component, base class for the physics compoentns
	 */
		class PhysicsComponent : public Component
		{
		protected:
			rp3d::ProxyShape* m_proxy; ///< joins the shape and thr ridgidbody
			rp3d::RigidBody* m_body; ///< the ridgid body
		public:
			PhysicsComponent() {}; ///< default coinstructor
			virtual void onAttach(GameObject* _parent) override; ///< what happends when attatched to the object
			virtual void onDetach() override; ///< what happens when detatching from an object
			virtual void onUpdate(float _deltaTime) override {};///< the update function runs every frame
			virtual void onEvent(Events::Event& _e) override {};///< when an event happens this is called
			virtual void receiveMessage(const ComponentMessage& _msg) override {};///< how to tinterperate messages
			virtual void enableGravity(bool _isEnabled); ///< turns gravity on
			virtual void addForce(glm::vec3 _force, glm::vec3 _point);///< adds a force to the ridgidbody
			virtual void addTorque(glm::vec3 _torque); ///< adds tourque to the ridgidbody
			virtual void setAngularVelocity(glm::vec3 _angularVelocity); ///<  sets the angular velocity
			virtual void setLinearVelocity(glm::vec3 _linearVelocity);///< sets the linear velocity
		};
	}
}