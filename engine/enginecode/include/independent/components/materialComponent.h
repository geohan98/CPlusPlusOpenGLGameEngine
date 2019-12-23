#pragma once
#include "components/component.h"
#include "renderer/material.h"

namespace Engine
{
	class MaterialComponent : public Component
	{
	private:
		std::shared_ptr<Material> m_material;
	public:
		MaterialComponent(const std::shared_ptr<Material>& material) : m_material(material) {}
		inline std::shared_ptr<Material> getMaterial() { return m_material; }
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

	};
}