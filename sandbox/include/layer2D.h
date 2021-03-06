#pragma once
#include "Headers/layers/layer.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/materialComponent.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/velocityComponent.h"
#include "Headers/events/applicationEvents.h"
#include "Headers/events/keyEvents.h"
#include "Headers/events/mouseEvents.h"

namespace Engine
{
	/**
	 *  2D Layer, Handles Game objects
	 */
	class Layer2D : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;			///< All the GameObjects
		std::vector<std::shared_ptr<Components::MaterialComponent>> m_materials;	///< All the material Components
		std::vector<std::shared_ptr<Components::PositionComponent>> m_positions;	///< All the position Components
		std::vector<std::shared_ptr<Components::VelocityComponent>> m_velocities;	///< All the velocity Components
		//Application Events
		bool onWindowResize(Events::WindowResize& e);				///< Window Resize Event
		bool onWindowClose(Events::WindowClose& e);					///< Window Close Event
		bool onWindowMoved(Events::WindowMoved& e);					///< Window Move Event
		bool onWindowLostFocus(Events::WindowLostFocus& e);			///< Window Lost Focus Event
		//Key Events
		bool onKeyPressed(Events::KeyPressed& e);					///< Key Press Event
		bool onKeyReleased(Events::KeyReleased& e);					///< Key Release Event
		bool onKeyTyped(Events::KeyTyped& e);						///< Key Type Event
		//Mouse Events
		bool onMouseMove(Events::MouseMoved& e);					///< Mouse Move Event
		bool onMouseScrolled(Events::MouseScrolled& e);				///< Mouse Scrolled Event
		bool onMouseButtonPressed(Events::MouseButtonPressed& e);	///< Mouse Button Press Event
		bool onMouseButtonReleased(Events::MouseButtonReleased& e);	///< Mouse Button Release Event
	public:
		Layer2D(const std::string& name = "2D Layer") : Layer(name) {}; ///< Constructor
		void onAttach() override;					///< Run on layer Attach
		void onDetach() override;					///< Run on Layer remove from layer stack
		void onUpdate(float deltaTime) override;	///< Run every Frame
		void onEvent(Events::Event& e) override;			///< Run on an Event
	};
}