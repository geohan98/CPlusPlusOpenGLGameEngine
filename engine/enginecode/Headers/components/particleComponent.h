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
		glm::vec2 scale;
		glm::vec4 colour;
		float lifetime;
		glm::vec3 linearVelocity;
		float angularVelocity;

		ParticleData() : position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(0.0f), scale(glm::vec2(1.0f, 1.0f)), colour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), lifetime(10.0f), linearVelocity(glm::vec3(0.0f, 0.0f, 0.0f)), angularVelocity(0.0f) {}

		ParticleData(glm::vec3 _position, float _rotation, glm::vec2 _scale, glm::vec4 _colour, float _lifetime, glm::vec3 _linearVelocity, float _angularVelocity)
		{
			position = _position;
			rotation = _rotation;
			scale = _scale;
			colour = _colour;
			lifetime = _lifetime;
			linearVelocity = _linearVelocity;
			angularVelocity = _angularVelocity;
		}
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
			std::vector<float> m_shaderData;

			float m_spawnRate = 10.0f;
			float m_lastSpawn = 0.0f;

			float m_minRotation = 0;
			float m_maxRotation = 89;
			glm::vec2 m_minScale = glm::vec2(1.0f, 1.0f);
			glm::vec2 m_maxScale = glm::vec2(1.0f, 1.0f);
			glm::vec4 m_minColor = glm::vec4(0.94510f, 0.15294f, 0.06667f, 0.5f);
			glm::vec4 m_maxColor = glm::vec4(0.96078f, 0.68627f, 0.09804f, 0.75f);
			float m_minLifetime = 2.0f;
			float m_maxLifetime = 3.0f;
			glm::vec3 m_minLinearVelocity = glm::vec3(-0.25f, 0.5f, -0.25f);
			glm::vec3 m_maxLinearVelocity = glm::vec3(0.25f, 1.0f, 0.25f);
			float m_minAngularVelocity = -90;
			float m_maxAngularVelocity = 90;

			bool m_gravity = true;

			void addParticle(int count = 1)
			{
				for (int i = 0; i < count; i++)
				{
					ParticleData particle = ParticleData();
					particle.rotation = glm::linearRand(m_minRotation, m_maxRotation);
					particle.scale = glm::linearRand(m_minScale, m_maxScale);
					float a = glm::linearRand(0.0f, 1.0f);
					particle.colour = glm::mix(m_minColor, m_maxColor, a);
					particle.lifetime = glm::linearRand(m_minLifetime, m_maxLifetime);
					particle.linearVelocity = glm::linearRand(m_minLinearVelocity, m_maxLinearVelocity);
					particle.angularVelocity = glm::linearRand(m_minAngularVelocity, m_maxAngularVelocity);
					m_particleData.push_back(particle);
				}
			}

		public:
			ParticleComponent()
			{
				m_shader = std::shared_ptr<Renderer::Shader>(Renderer::Shader::create("assets/shaders/particle.shader"));
				Renderer::VertexBufferLayout layout = { Renderer::ShaderDataType::Float3,Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float2,Renderer::ShaderDataType::Float4 };
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

				if (((Systems::Time::getTimeNow() - m_lastSpawn) / 1000000000) >= 1.0f / m_spawnRate)
				{
					m_lastSpawn = Systems::Time::getTimeNow();
					addParticle();
				}


				if (m_particleData.size() > 0)
				{
					auto it = m_particleData.begin();
					while (it != m_particleData.end())
					{
						it->lifetime -= deltaTime;
						if (it->lifetime <= 0)
						{
							it = m_particleData.erase(it);
						}
						else
						{
							it++;
						}
					}
				}

				LOG_CORE_WARN("Number Of Particles: {0}", m_particleData.size());

				if (m_particleData.size() > 0)
				{
					std::vector<float> vertexData(10 * m_particleData.size());

					for (int i = 0; i < m_particleData.size(); i++)
					{
						m_particleData[i].position += m_particleData[i].linearVelocity * deltaTime;
						m_particleData[i].rotation += m_particleData[i].angularVelocity * deltaTime;

						int start = i * 10;
						vertexData[start + 0] = m_particleData[i].position.x;
						vertexData[start + 1] = m_particleData[i].position.y;
						vertexData[start + 2] = m_particleData[i].position.z;
						vertexData[start + 3] = m_particleData[i].rotation;
						vertexData[start + 4] = m_particleData[i].scale.x;
						vertexData[start + 5] = m_particleData[i].scale.y;
						vertexData[start + 6] = m_particleData[i].colour.x;
						vertexData[start + 7] = m_particleData[i].colour.y;
						vertexData[start + 8] = m_particleData[i].colour.z;
						vertexData[start + 9] = m_particleData[i].colour.w;
					}
					m_vertexBuffer->edit(&vertexData[0], vertexData.size() / 10);
					return;
				}
				m_vertexBuffer->edit(nullptr, 0);

			}
		};
	}
}