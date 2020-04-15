#pragma once
#include <any>
#include <memory>

typedef int MsgType;

namespace Engine
{
	class ISubscriber;

	class ISubject
	{
	public:
		virtual void addSubscriber(std::shared_ptr<ISubscriber> _subscriber) = 0;
		virtual void removeSubscriber(std::shared_ptr<ISubscriber> _subscriber) = 0;
		virtual void notifySubscribers(MsgType _type, std::any _data) = 0;
	};
}