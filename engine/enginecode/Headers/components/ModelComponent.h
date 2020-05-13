#pragma once
#include "Headers/components/component.h"
#include "Headers/renderer/model.h"
namespace Engine
{
	namespace Components
	{

		class ModelComponent : public Component
		{
		private:
			std::shared_ptr<Model> m_model;
		public:
			ModelComponent(const std::string& filepath);
			~ModelComponent();
			void onUpdate(float deltaTime); ///< Called Every Frame
			void receiveMessage(const ComponentMessage& msg); ///< Receive a message from another component
			std::vector<std::shared_ptr<Renderer::Material>> getMaterials(); ///< returns the materials of the model
			void setDataElement(const std::string& dataName, void* data); ///< sets the data element
		};


	}

}

