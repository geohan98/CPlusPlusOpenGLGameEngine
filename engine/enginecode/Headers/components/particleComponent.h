#pragma once
#include "Headers/components/component.h"
#include "Headers/renderer/material.h"
#include "Headers/renderer/shader.h"
#include "Headers/renderer/vertexBuffer.h"
#include "Headers/systems/time.h"
#include <vector>
#include "Headers/systems/time.h"
#include <glm/gtc/random.hpp>


namespace Engine
{

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

		ParticleData() {}
		ParticleData(glm::vec3 _position, float _rotation, float _startScale, float _endScale, glm::vec4 _startColour, glm::vec4 _endColour, glm::vec3 _linearVelocity, float _angularVelocity, float _lifetime) :
			position(_position), rotation(_rotation), scale(_startScale), startScale(_startScale), endScale(_endScale), colour(_startColour), startColour(_startColour), endColour(_endColour), linearVelocity(_linearVelocity), angularVelocity(_angularVelocity), lifetime(_lifetime), timeleft(_lifetime) {}
	};


	namespace Components
	{
		class ParticleComponent : public Component
		{
		private:
			std::shared_ptr<Renderer::Material> m_material;
			std::shared_ptr<Renderer::Shader> m_shader;
			std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;
			std::vector<ParticleData> m_particleData;

			//System Data
			float m_lastSpawn;
			float m_spawnRate = 10.0f;
			//Rotation
			float m_minStartRotation = 0.0f;
			float m_maxStartRotation = 45.0f;
			//Scale - Start
			float m_minStartScale = 0.5f;
			float m_maxStartScale = 1.0f;
			//Scale - End
			float m_minEndScale = 0.0f;
			float m_maxEndScale = 0.0f;
			//Colour - Start
			glm::vec4 m_minStartColour = glm::vec4(0.94510f, 0.15294f, 0.06667f, 1.0f);
			glm::vec4 m_maxStartColour = glm::vec4(0.94510f, 0.15294f, 0.06667f, 0.1f);
			//Colour - End
			glm::vec4 m_minEndColour = glm::vec4(0.96078f, 0.68627f, 0.09804f, 1.0f);
			glm::vec4 m_maxEndColour = glm::vec4(0.96078f, 0.68627f, 0.09804f, 0.1f);
			//Linear Velocity
			glm::vec3 m_minStartLinearVelocity = glm::vec3(-1.0f, 2.0f, -1.0f);
			glm::vec3 m_maxStartLinearVelocity = glm::vec3(1.0f, 2.0f, 1.0f);
			//AngularVelocity
			float m_minStartAngularVelocity = -60.0f;
			float m_maxStartAngularVelocity = 60.0f;
			//LifeTime
			float m_minStartLifetime = 1.5f;
			float m_maxStartLifetime = 2.0f;
			//Gravity
			bool m_gravity;

			void addParticle(int count = 1)
			{
				for (int i = 0; i < count; i++)
				{
					m_particleData.push_back(ParticleData(glm::vec3(0.0f), glm::linearRand(m_minStartRotation, m_maxStartRotation), glm::linearRand(m_minStartScale, m_maxStartScale), glm::linearRand(m_minEndScale, m_maxEndScale), glm::linearRand(m_minStartColour, m_maxStartColour), glm::linearRand(m_minEndColour, m_maxEndColour), glm::linearRand(m_minStartLinearVelocity, m_maxStartLinearVelocity), glm::linearRand(m_minStartAngularVelocity, m_maxStartAngularVelocity), glm::linearRand(m_minStartLifetime, m_maxStartLifetime)));
				}
			}

		public:
			ParticleComponent()
			{
				m_shader = std::shared_ptr<Renderer::Shader>(Renderer::Shader::create("assets/shaders/particle.shader"));
				Renderer::VertexBufferLayout layout = { Renderer::ShaderDataType::Float3,Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float4 };
				m_vertexBuffer = std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(nullptr, 0, layout));
				m_material = std::shared_ptr<Renderer::Material>(Renderer::Material::create(m_shader, m_vertexBuffer));
				m_lastSpawn = Systems::Time::getTimeNow();
			}
			inline std::shared_ptr<Renderer::Material> getMaterial() { return m_material; }
			void receiveMessage(const ComponentMessage& msg) override
			{
				switch (msg.m_msgType)
				{
				case ComponentMessageType::UniformSet:
					std::pair<std::string, void*> data = std::any_cast<std::pair<std::string, void*>>(msg.m_msgData);
					m_material->setDataElement(data.first, data.second);
					return;
				}
			}
			void onUpdate(float deltaTime) override
			{
				if ((Systems::Time::getTimeNow() - m_lastSpawn) / 1000000000.0f >= 1.0f / m_spawnRate)
				{
					addParticle();
					m_lastSpawn = Systems::Time::getTimeNow();
				}


				//Remove Old Particles
				if (!m_particleData.empty())
				{
					std::vector<ParticleData>::iterator it = m_particleData.begin();

					while (it != m_particleData.end())
					{
						it->position += it->linearVelocity * deltaTime;
						it->rotation += it->angularVelocity * deltaTime;
						it->scale = glm::mix(it->endScale, it->startScale, it->timeleft / it->lifetime);
						it->colour = glm::mix(it->endColour, it->startColour, it->timeleft / it->lifetime);
						it->timeleft -= deltaTime;

						if (it->timeleft < 0)
						{
							// TODO: Replace with swap-one-off-the-end algo.
							it = m_particleData.erase(it);
						}
						else
						{
							it++;
						}

					}
				}
				if (!m_particleData.empty())
				{
					std::vector<float> vertexData(9 * m_particleData.size());

					for (int i = 0; i < m_particleData.size(); i++)
					{
						int start = i * 9;

						vertexData[start + 0] = m_particleData[i].position.x;//X
						vertexData[start + 1] = m_particleData[i].position.y;//Y
						vertexData[start + 2] = m_particleData[i].position.z;//Z
						vertexData[start + 3] = m_particleData[i].rotation;//ROT
						vertexData[start + 4] = m_particleData[i].scale;//SCALE
						vertexData[start + 5] = m_particleData[i].colour.x;//R
						vertexData[start + 6] = m_particleData[i].colour.y;//G
						vertexData[start + 7] = m_particleData[i].colour.z;//B
						vertexData[start + 8] = m_particleData[i].colour.w;//A

					}
					m_vertexBuffer->edit(&vertexData[0], vertexData.size() / 9);
				}
				else
				{
					m_vertexBuffer->edit(nullptr, 0);
				}

			}
		};
	}
}