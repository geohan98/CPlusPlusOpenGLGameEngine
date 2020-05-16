#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "Headers\components\particleComponent.h"

#include "Headers/systems/time.h"
#include "Headers/renderer/material.h"
#include "Headers/renderer/shader.h"
#include "Headers/renderer/vertexBuffer.h"
#include "Headers/renderer/vertexArray.h"
#include "Headers/renderer/shaderDataType.h"
#include "Headers/renderer/vertexBufferLayout.h"

namespace Engine
{
	namespace Components
	{
		ParticleComponent::ParticleComponent(float _spawnRate, float _size, float _rotation, glm::vec4 _colour, glm::vec3 _linarVelocity, float _angularVelocity, float _lifetime)
		{
			m_shader = std::shared_ptr<Renderer::Shader>(Renderer::Shader::create("assets/shaders/particle.shader"));
			Renderer::VertexBufferLayout layout = { Renderer::ShaderDataType::Float3,Engine::Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float4 };
			m_vertexBuffer = std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(nullptr, 0, layout));
			m_vertexArray = std::shared_ptr<Renderer::VertexArray>(Renderer::VertexArray::create());
			m_vertexArray->setVertexBuffer(m_vertexBuffer);
			m_material = std::shared_ptr<Renderer::Material>(Renderer::Material::create(m_shader, m_vertexArray));
			m_lastSpawn = Systems::Time::getTimeNowMillisecconds();

			m_properties.m_spawnRate = _spawnRate;

			m_properties.m_minStartScale = _size;
			m_properties.m_maxStartScale = _size;
			m_properties.m_minEndScale = _size;
			m_properties.m_maxEndScale = _size;

			m_properties.m_minStartRotation = _rotation;
			m_properties.m_maxStartRotation = _rotation;

			m_properties.m_minStartColour = _colour;
			m_properties.m_maxStartColour = _colour;
			m_properties.m_minEndColour = _colour;
			m_properties.m_maxEndColour = _colour;

			m_properties.m_minStartLinearVelocity = _linarVelocity;
			m_properties.m_maxStartLinearVelocity = _linarVelocity;

			m_properties.m_minStartAngularVelocity = _angularVelocity;
			m_properties.m_maxStartAngularVelocity = _angularVelocity;

			m_properties.m_minStartLifetime = _lifetime;
			m_properties.m_maxStartLifetime = _lifetime;
		}
		ParticleComponent::ParticleComponent(ParticleSystemProperties _properties)
		{
			m_shader = std::shared_ptr<Renderer::Shader>(Renderer::Shader::create("assets/shaders/particle.shader"));
			Renderer::VertexBufferLayout layout = { Renderer::ShaderDataType::Float3,Engine::Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float4 };
			m_vertexBuffer = std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(nullptr, 0, layout));
			m_vertexArray = std::shared_ptr<Renderer::VertexArray>(Renderer::VertexArray::create());
			m_vertexArray->setVertexBuffer(m_vertexBuffer);
			m_material = std::shared_ptr<Renderer::Material>(Renderer::Material::create(m_shader, m_vertexArray));
			m_lastSpawn = Systems::Time::getTimeNowMillisecconds();

			m_properties = _properties;
		}
		void ParticleComponent::addParticle(int count)
		{
			for (int i = 0; i < count; i++)
			{
				m_particleData.push_back(ParticleData(glm::vec3(0.0f), glm::linearRand(m_properties.m_minStartRotation, m_properties.m_maxStartRotation), glm::linearRand(m_properties.m_minStartScale, m_properties.m_maxStartScale), glm::linearRand(m_properties.m_minEndScale, m_properties.m_maxEndScale), glm::linearRand(m_properties.m_minStartColour, m_properties.m_maxStartColour), glm::linearRand(m_properties.m_minEndColour, m_properties.m_maxEndColour), glm::linearRand(m_properties.m_minStartLinearVelocity, m_properties.m_maxStartLinearVelocity), glm::linearRand(m_properties.m_minStartAngularVelocity, m_properties.m_maxStartAngularVelocity), glm::linearRand(m_properties.m_minStartLifetime, m_properties.m_maxStartLifetime)));
			}
		}
		void ParticleComponent::onUpdate(float deltaTime)
		{

			int count = std::floor((Systems::Time::getTimeNowMillisecconds() - m_lastSpawn) / ((1.0f / m_properties.m_spawnRate) * 1000.0f));
			if (count > 0)
			{
				addParticle(count);
				m_lastSpawn = Systems::Time::getTimeNowMillisecconds();
			}

			//Remove Old Particles
			if (!m_particleData.empty())
			{
				std::vector<ParticleData>::iterator it = m_particleData.begin();

				while (it != m_particleData.end())
				{
					if (m_properties.m_gravity) it->linearVelocity.y += -9.81f * deltaTime;
					it->linearVelocity -= it->linearVelocity * m_properties.m_drag * deltaTime;
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
		void ParticleComponent::reset(ParticleSystemProperties* _properties)
		{
			m_properties = *_properties;
			m_particleData.clear();
			m_lastSpawn = Systems::Time::getTimeNowMillisecconds();
		}
		void ParticleComponent::receiveMessage(const ComponentMessage& msg)
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::UniformSet:
				std::pair<std::string, void*> data = std::any_cast<std::pair<std::string, void*>>(msg.m_msgData);
				m_material->setDataElement(data.first, data.second);
				return;
			}
		}
	}
}