#pragma once
#include "Headers/components/component.h"
#include <vector>
#include <glm/gtc/random.hpp>
#include <glm/glm.hpp>


namespace Engine
{
	struct SystemProperties
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
		float m_minEndScale = 1.0f;
		float m_maxEndScale = 1.0f;
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

	namespace Renderer
	{
		class Material;
		class Shader;
		class VertexBuffer;
		class VertexArray;
	}

	namespace Components
	{
		class ParticleComponent : public Component
		{
		private:
			SystemProperties m_properties;
			float m_lastSpawn;
			std::shared_ptr<Renderer::Material> m_material;
			std::shared_ptr<Renderer::Shader> m_shader;
			std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;
			std::shared_ptr<Renderer::VertexArray> m_vertexArray;
			std::vector<ParticleData> m_particleData;
			void addParticle(int count = 1);
		public:
			ParticleComponent(float _spawnRate = 1.0f, float _size = 0.25f, float _rotation = 0.0f, glm::vec4 _colour = glm::vec4(1, 1, 1, 1), glm::vec3 _linarVelocity = glm::vec3(0, 1, 0), float _angularVelocity = 0.0f, float _lifetime = 1.0f);
			ParticleComponent(SystemProperties _properties);
			inline std::shared_ptr<Renderer::Material> getMaterial() { return m_material; }
			void receiveMessage(const ComponentMessage& msg) override;
			void onUpdate(float deltaTime) override;
			void reset(SystemProperties* _properties);
		};
	}
}