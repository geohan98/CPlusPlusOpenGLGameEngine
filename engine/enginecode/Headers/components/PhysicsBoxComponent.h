#pragma once
#include "Headers/components/physicsComponent.h"
#include "reactphysics3d.h"
#include "glm/glm.hpp"

namespace Engine {
	namespace Components {
		/**
	 *  PhysicsBoxComponent, A box shaped physics object
	 */
		class PhysicsBoxComponent : public PhysicsComponent
		{
		private:
			rp3d::BoxShape* m_shape;
		public:
			PhysicsBoxComponent(glm::vec3 Position, glm::vec4 Orientation, glm::vec3 boxSize, float density, bool useGravity = true, reactphysics3d::BodyType type = reactphysics3d::BodyType::DYNAMIC);
			void onAttach(GameObject* parent) override { m_parent = parent; } ///< Run When Component is added to GameObject
			void onDetach() override; ///< Run When Component is Removed From Parent
			void onUpdate(float deltaTime) override; ///< Called Every Frame
		};

	}
}