#pragma once
#include "events/event.h"
#include <any>

namespace Engine
{
	class GameObject;

	/**
	 *  Component Message Type
	 */
	enum class ComponentMessageType
	{
		None = 0,
		PositionIntergrate, PositionSet, RelativePositionSet,
		VelocityIntergrate, VelocitySetLinear, VelocitySetAngular,
		AccelerationSet,
		KeyPressed, KeyReleased, MouseButton, MouseScroll, MouseMoved,
		UniformSet, TextureSet, TextureBind
	};

	/**
	 *  Component Message, Send messages to other components
	 */
	class ComponentMessage
	{
	public:
		ComponentMessage(ComponentMessageType type, std::any data) : m_msgType(type), m_msgData(data) {} ///< Constructor
		ComponentMessageType m_msgType; ///< Message Type Enum
		std::any m_msgData; ///< Message Data
	};

	/**
	 *  Camera, Abstract Virtual Class, Handles Projection and View Matrix Calculation
	 */
	class Component
	{
	protected:
		std::string m_name = "Component"; ///< Component Name
		GameObject* m_parent = nullptr; ///< Component Parent
		virtual void sendMessage(const ComponentMessage& msg); ///< Send message to all Components of the Parent
	public:
		virtual void onAttach(GameObject* parent) { m_parent = parent; } ///< Run When Component is added to GameObject
		virtual void onDetach() { m_parent = nullptr; } ///< Run When Component is Removed From Parent
		virtual void onUpdate(float deltaTime) {}; ///< Called Every Frame
		virtual void onEvent(Events::Event& e) {} ///< Called on an Event
		virtual void receiveMessage(const ComponentMessage& msg) = 0; ///< Receive a message from another component
	};

}