#include "engine_pch.h"
#include "Headers/components/ModelComponent.h"

namespace Engine
{
	namespace Components {
		ModelComponent::ModelComponent(const std::string& filepath)
		{
			m_model = std::shared_ptr<Model>(new Model(filepath));
		}

		ModelComponent::~ModelComponent()
		{

		}

		void ModelComponent::onUpdate(float deltaTime)
		{

		}

		void ModelComponent::receiveMessage(const ComponentMessage& msg)
		{


			switch (msg.m_msgType)
			{
			case ComponentMessageType::UniformSet:
				std::pair<std::string, void*> data = std::any_cast<std::pair<std::string, void*>>(msg.m_msgData);
				for each (auto mat in m_model->getMaterials())
				{
					mat->setDataElement(data.first, data.second);
				}

				return;
			}
		}
		std::vector<std::shared_ptr<Renderer::Material>> ModelComponent::getMaterials()
		{
			return m_model->getMaterials();
		}
		void ModelComponent::setDataElement(const std::string& dataName, void* data)
		{
			for each (auto mat in m_model->getMaterials())
			{
				mat->setDataElement(dataName, data);
			}
		}
	}
}