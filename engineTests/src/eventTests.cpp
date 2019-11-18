#include "eventTests.h"

TEST(Events, DispatchTrue)
{
	Engine::WindowResize event(1920, 1080);
	Engine::EventDispatcher dispatcher(event);
	bool result = dispatcher.dispatch<Engine::WindowResize>(std::bind(onResizeTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchFalse)
{
	Engine::WindowClose event;
	Engine::EventDispatcher dispatcher(event);
	bool result = dispatcher.dispatch<Engine::WindowResize>(std::bind(onResizeTrue, std::placeholders::_1));
	EXPECT_FALSE(result);
}