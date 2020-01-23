#pragma once
#include "../components/component.h"
#include "../renderer/material.h"

namespace Engine
{
	
		/**
		 *  Material Component, Holds Shader and Geometry Data
		 */
		class MaterialComponent : public Component
		{
		private:
			std::shared_ptr<Renderer::Material> m_material; ///< Smart Pointer To Material
		public:
			MaterialComponent(const std::shared_ptr<Renderer::Material>& material) : m_material(material) {} ///< Constructor
			inline std::shared_ptr<Renderer::Material> getMaterial() { return m_material; } ///< Return the Material
			void receiveMessage(const ComponentMessage& msg) override ///< Override receive Message and deal with data, Sets Shader Uniform
			{
				switch (msg.m_msgType)
				{
				case ComponentMessageType::UniformSet:
					std::pair<std::string, void*> data = std::any_cast<std::pair<std::string, void*>>(msg.m_msgData);
					m_material->setDataElement(data.first, data.second);
					return;
				}
			}

		};
	}
