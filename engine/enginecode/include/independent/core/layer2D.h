#pragma once
#pragma once
#include "core/layer.h"

namespace Engine
{
	class Layer2D : public Layer
	{
	public:
		Layer2D(const std::string& name = "Game Layer") : Layer(name) {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
	};
}