#pragma once
#include "Headers/components/component.h"
#include "Headers/renderer/material.h"
#include "Headers/renderer/shader.h"
#include "Headers/renderer/vertexArray.h"
#include "Headers/renderer/vertexBuffer.h"
#include "Headers/renderer/indexBuffer.h"

#include <vector>


namespace Engine
{
	namespace Components
	{
		class ParticleComponent : public Component
		{
		private:
			std::shared_ptr<Renderer::Material> m_material;
			std::shared_ptr<Renderer::Shader> m_shader;
			std::shared_ptr<Renderer::VertexArray> m_vertexArray;
			std::shared_ptr<Renderer::VertexBuffer> m_vertexBuffer;
			std::shared_ptr<Renderer::IndexBuffer> m_indexBuffer;

			std::vector<float> m_vertexData;
		public:
			ParticleComponent() {}
			inline std::shared_ptr<Renderer::Material> getMaterial() { return m_material; }
			void receiveMessage(const ComponentMessage& msg) override {}
		};
	}
}