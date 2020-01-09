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
	/**
	 *  Game Layer, Handles Game objects
	 */
	class GameLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;			///< All the GameObjects
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;	///< All the material Components
		std::vector<std::shared_ptr<PositionComponent>> m_positions;	///< All the position Components
		std::vector<std::shared_ptr<VelocityComponent>> m_velocities;	///< All the velocity Components
		//Application Events
		bool onWindowResize(WindowResize& e);				///< Window Resize Event
		bool onWindowClose(WindowClose& e);					///< Window Close Event
		bool onWindowMoved(WindowMoved& e);					///< Window Move Event
		bool onWindowLostFocus(WindowLostFocus& e);			///< Window Lost Focus Event
		//Key Events
		bool onKeyPressed(KeyPressed& e);					///< Key Press Event
		bool onKeyReleased(KeyReleased& e);					///< Key Release Event
		bool onKeyTyped(KeyTyped& e);						///< Key Type Event
		//Mouse Events
		bool onMouseMove(MouseMoved& e);					///< Mouse Move Event
		bool onMouseScrolled(MouseScrolled& e);				///< Mouse Scrolled Event
		bool onMouseButtonPressed(MouseButtonPressed& e);	///< Mouse Button Press Event
		bool onMouseButtonReleased(MouseButtonReleased& e);	///< Mouse Button Release Event
	public:
		GameLayer(const std::string& name = "Game Layer") : Layer(name) {}; ///< Constructor
		void onAttach() override;					///< Run on layer Attach
		void onDetach() override;					///< Run on Layer remove from layer stack
		void onUpdate(float deltaTime) override;	///< Run every Frame
		void onEvent(Event& e) override;			///< Run on an Event
	};
}