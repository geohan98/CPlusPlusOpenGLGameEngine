#pragma once
#include "Headers/components/component.h"
#include "reactphysics3d.h"
#include "glm/glm.hpp"

namespace Engine {
	namespace Components {
		class PhysicsComponent : public Component
		{
		protected:
			rp3d::ProxyShape* m_proxy;
			rp3d::RigidBody* m_body;
		public:
			PhysicsComponent() {};
			virtual void onAttach(GameObject* _parent) override;
			virtual void onDetach() override;
			virtual void onUpdate(float _deltaTime) override {};
			virtual void onEvent(Events::Event& _e) override {};
			virtual void receiveMessage(const ComponentMessage& _msg) override {};
			virtual void enableGravity(bool _isEnabled);
			virtual void addForce(glm::vec3 _force, glm::vec3 _point);
			virtual void addTorque(glm::vec3 _torque);
			virtual void setAngularVelocity(glm::vec3 _angularVelocity);
			virtual void setLinearVelocity(glm::vec3 _linearVelocity);
		};
	}
}