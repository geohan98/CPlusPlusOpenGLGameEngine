#pragma once
#include "Headers/components/physicsComponent.h"
#include "reactphysics3d.h"
#include "glm/glm.hpp"
#include "Headers/audio/audio.h"

namespace Engine {

	namespace Components {
		/**
	 *  PhysicsSphereComponent, A spherical physics object
	 */
		class PhysicsSphereComponent : public PhysicsComponent
		{
		private:
			rp3d::SphereShape* m_shape; ///< the components shape
		public:
			PhysicsSphereComponent(glm::vec3 Position, glm::vec4 Orientation, float radius, float density, bool useGravity = true, reactphysics3d::BodyType type = reactphysics3d::BodyType::DYNAMIC); ///< constructor
			void onAttach(GameObject* parent) override { m_parent = parent; } ///< Run When Component is added to GameObject
			void onDetach() override; ///< Run When Component is Removed From Parent
			void onUpdate(float deltaTime) override; ///< Called Every Frame
		};

	}
}