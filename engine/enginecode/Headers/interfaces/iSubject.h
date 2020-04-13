#pragma once
#include <any>

typedef int MsgType;

namespace Engine
{
	class ISubscriber;

	class ISubject
	{
	public:
		virtual void addSubscriber(ISubscriber* _subscriber) = 0;
		virtual void removeSubscriber(ISubscriber* _subscriber) = 0;
		virtual void notifySubscribers(MsgType _type, std::any _data) = 0;
	};
}