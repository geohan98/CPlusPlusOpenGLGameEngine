#pragma once
#include "core/layer.h"

namespace Engine
{
	class GameLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<Material>> m_labelsmaterials;
		std::vector<std::shared_ptr<UniformBuffer>> m_uniformBuffers;
		std::vector<glm::mat4> m_models;
		SceneData m_sceneData;
	public:
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
	};
}