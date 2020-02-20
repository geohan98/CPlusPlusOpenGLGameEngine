#pragma once
#include "Headers/components/component.h"
#include "Headers/renderer/material.h"
#include "Headers/renderer/shader.h"
#include "Headers/renderer/vertexBuffer.h"

#include <vector>
#include "Headers/systems/time.h"


namespace Engine
{

	struct ParticleData
	{
		glm::vec3 position;
		float rotation;
		glm::vec2 scale;
		glm::vec4 colour;
		glm::vec3 velocity;
		float spawnTime;
	};


	namespace Components
	{
		class ParticleComponent : public Component
		{
		private:
			std::shared_ptr<Renderer::Material> m_material;
			std::shared_ptr<Renderer::Shader> m_shader;
			std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;

			std::vector<ParticleData> m_data;

			float m_spawnRate = 1.0f;
			int m_particleCount;
			int m_maxParticles = 10;
			float m_particleLifetime;
			glm::vec4 m_defualtColour = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

			float vertices[100];
		public:
			ParticleComponent()
			{
				m_shader = std::shared_ptr<Renderer::Shader>(Renderer::Shader::create("assets/shaders/particle.shader"));
				Renderer::VertexBufferLayout layout = { Renderer::ShaderDataType::Float3,Renderer::ShaderDataType::Float,Renderer::ShaderDataType::Float2,Renderer::ShaderDataType::Float4 };
				m_vertexBuffer = std::shared_ptr<Renderer::VertexBuffer>(Renderer::VertexBuffer::create(vertices, m_particleCount, layout));
				m_material = std::shared_ptr<Renderer::Material>(Renderer::Material::create(m_shader, m_vertexBuffer));
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
				if (TIME_APP_START - m_data.back().spawnTime >= m_spawnRate / 1.0f)
				{

				}
			}
		};
	}
}