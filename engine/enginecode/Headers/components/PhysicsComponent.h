#pragma once

#include "Headers/components/component.h"
#include "glm/glm.hpp"
#include "Headers/systems/Physics.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class btCollisionObject;
class btCollisionShape;
class btTransform;

namespace Engine {


	class PhysicsComponent : public Component {

	public:
		PhysicsComponent() {}
		PhysicsComponent(glm::vec3 boxSize, glm::vec3 transform);
		void onUpdate(float deltaTime) override; ///< Called Every Frame

		void receiveMessage(const ComponentMessage& msg) override; ///< Receive a message from another component
	private:
		std::shared_ptr<btCollisionObject> m_collision;
		std::shared_ptr<btCollisionShape> m_collisionShape;
		std::shared_ptr<btTransform> m_transform;


	};
}