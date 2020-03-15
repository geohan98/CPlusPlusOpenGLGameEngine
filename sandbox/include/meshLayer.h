#pragma once

#include "Headers/layers/layer.h"

namespace Engine
{
	class MeshLayer : public Layer
	{
	public:
		MeshLayer(const std::string& name = "Game Layer") : Layer(name) {};
		~MeshLayer() {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float deltaTime) override;
		void onEvent(Events::Event& e) override;
	};
}