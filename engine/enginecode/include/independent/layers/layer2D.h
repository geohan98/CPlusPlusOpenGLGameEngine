#pragma once
#include "layers/layer.h"
#include "core/gameObject.h"
#include "components/materialComponent.h"
#include "components/PositionComponent.h"
#include "components/velocityComponent.h"
#include "events/applicationEvents.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"

namespace Engine
{
	class Layer2D : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;
		std::vector<std::shared_ptr<PositionComponent>> m_positions;
		std::vector<std::shared_ptr<VelocityComponent>> m_velocities;
		//Application Events
		bool onWindowResize(WindowResize& e);
		bool onWindowClose(WindowClose& e);
		bool onWindowMoved(WindowMoved& e);
		bool onWindowLostFocus(WindowLostFocus& e);
		//Key Events
		bool onKeyPressed(KeyPressed& e);
		bool onKeyReleased(KeyReleased& e);
		bool onKeyTyped(KeyTyped& e);
		//Mouse Events
		bool onMouseMove(MouseMoved& e);
		bool onMouseScrolled(MouseScrolled& e);
		bool onMouseButtonPressed(MouseButtonPressed& e);
		bool onMouseButtonReleased(MouseButtonReleased& e);
	public:
		Layer2D(const std::string& name = "2D Layer") : Layer(name) {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float deltaTime) override;
		void onEvent(Event& e) override;
	};
}