#pragma once
#include "Headers/components/component.h"
#include <vector>
#include <glm/gtc/random.hpp>
#include <glm/glm.hpp>


namespace Engine
{
	namespace Renderer
	{
		class Material;
		class Shader;
		class VertexBuffer;
		class VertexArray;
	}

	struct ParticleSystemProperties
	{
		//System Data
		float m_spawnRate = 1;
		//Rotation
		float m_minStartRotation = 0.0f;
		float m_maxStartRotation = 0.0f;
		//Scale - Start
		float m_minStartScale = 1.0f;
		float m_maxStartScale = 1.0f;
		//Scale - End
		float m_minEndScale = 0.1f;
		float m_maxEndScale = 0.1f;
		//Colour - Start
		glm::vec4 m_minStartColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 m_maxStartColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		//Colour - End
		glm::vec4 m_minEndColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 m_maxEndColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		//Linear Velocity
		glm::vec3 m_minStartLinearVelocity = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_maxStartLinearVelocity = glm::vec3(0.0f, 1.0f, 0.0f);
		//AngularVelocity
		float m_minStartAngularVelocity = 0.0f;
		float m_maxStartAngularVelocity = 0.0f;
		//LifeTime
		float m_minStartLifetime = 1.0f;
		float m_maxStartLifetime = 1.0f;
		//Gravity
		bool m_gravity;
	};

	struct ParticleData
	{
		glm::vec3 position;
		float rotation;
		float scale;
		float startScale;
		float endScale;
		glm::vec4 colour;
		glm::vec4 startColour;
		glm::vec4 endColour;
		glm::vec3 linearVelocity;
		float angularVelocity;
		float lifetime;
		float timeleft;

		ParticleData(glm::vec3 _position, float _rotation, float _startScale, float _endScale, glm::vec4 _startColour, glm::vec4 _endColour, glm::vec3 _linearVelocity, float _angularVelocity, float _lifetime) :
			position(_position), rotation(_rotation), scale(_startScale), startScale(_startScale), endScale(_endScale), colour(_startColour), startColour(_startColour), endColour(_endColour), linearVelocity(_linearVelocity), angularVelocity(_angularVelocity), lifetime(_lifetime), timeleft(_lifetime) {}
	};

	namespace Components
	{
		class ParticleComponent : public Component
		{
		private:
			ParticleSystemProperties m_properties; ///< The configuration of the particle sysetm
			float m_lastSpawn;///< Last time one or more particles where spawned
			std::shared_ptr<Renderer::Material> m_material; ///< The material for the particle system
			std::shared_ptr<Renderer::Shader> m_shader; ///< The Shader for the particle system
			std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer; ///< The VBO for the particle system
			std::shared_ptr<Renderer::VertexArray> m_vertexArray; ///< The VAO for the particle system
			std::vector<ParticleData> m_particleData; ///< List of all the currently active particles
			void addParticle(int count = 1); ///< Add one or more particles to the system using the particle system properties
		public:
			ParticleComponent(float _spawnRate = 1.0f, float _size = 0.25f, float _rotation = 0.0f, glm::vec4 _colour = glm::vec4(1, 1, 1, 1), glm::vec3 _linarVelocity = glm::vec3(0, 1, 0), float _angularVelocity = 0.0f, float _lifetime = 1.0f); ///< Constructor with induvidual parameters
			ParticleComponent(ParticleSystemProperties _properties); ///< Construcotr with particle system properties
			inline std::shared_ptr<Renderer::Material> getMaterial() { return m_material; } ///< Return the material of the particle system
			void receiveMessage(const ComponentMessage& msg) override;  ///< Component Recive Message
			void onUpdate(float deltaTime) override; ///< Component on Update, upddate all particles and add new ones if needed
			void reset(ParticleSystemProperties* _properties); ///< Remove all particle data and use the new system properties
		};
	}
}