#pragma once
#include "core/layer.h"

namespace Engine
{
	class TextLable;

	class UILayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<TextLable>> m_lables;
		std::shared_ptr<UniformBuffer> m_uniformBuffer;
		SceneData m_sceneData;
	public:
		UILayer(const std::string& name = "UI Layer") : Layer(name) {}
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
	};
}