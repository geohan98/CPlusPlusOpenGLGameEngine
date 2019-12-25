#pragma once
#include "events/event.h"
#include <any>

namespace Engine
{
	class GameObject;

	enum class ComponentMessageType
	{
		None = 0,
		PositionIntergrate, PositionSet, RelativePositionSet,
		VelocityIntergrate, VelocitySetLinear, VelocitySetAngular,
		AccelerationSet,
		KeyPressed, KeyReleased, MouseButton, MouseScroll, MouseMoved,
		UniformSet, TextureSet
	};
	class ComponentMessage
	{
	public:
		ComponentMessage(ComponentMessageType type, std::any data) : m_msgType(type), m_msgData(data) {}
		ComponentMessageType m_msgType;
		std::any m_msgData;
	};

	class Component
	{
	protected:
		std::string m_name = "Component";
		GameObject* m_parent = nullptr;
		virtual void sendMessage(const ComponentMessage& msg);
	public:
		virtual void onAttach(GameObject* parent) { m_parent = parent; }
		virtual void onDetach() { m_parent = nullptr; }
		virtual void onUpdate(float timestep) {};
		virtual void onEvent(Event& e) {}
		virtual void receiveMessage(const ComponentMessage& msg) = 0;
	};

}