#pragma once
#include <any>

typedef int MsgType;

namespace Engine
{
	class ISubscriber
	{
	public:
		virtual void beNotified(MsgType _type, std::any _data) = 0;
	};
}