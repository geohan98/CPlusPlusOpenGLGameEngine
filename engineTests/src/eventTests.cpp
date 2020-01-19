#include "eventTests.h"

TEST(Events, ResizeConstructorTrue)
{
	Engine::Events::WindowResize event(1920, 1080);
	int width = event.getWidth();
	int height = event.getHeight();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(width, 1920);
	EXPECT_EQ(height, 1080);
}

TEST(Events, ResizeConstructorFalse)
{
	Engine::Events::WindowResize event(1920, 1080);
	int width = event.getWidth();
	int height = event.getHeight();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_NE(width, 192);
	EXPECT_NE(height, 108);
}

TEST(Events, MouseMoveContrusctorXTrue)
{
	Engine::Events::MouseMoved event(1, 0);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(posX, 1);
	EXPECT_EQ(posY, 0);
}

TEST(Events, MouseMoveContrusctorXFalse)
{
	Engine::Events::MouseMoved event(1, 0);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_NE(posX, 0);
	EXPECT_EQ(posY, 0);
}


TEST(Events, MouseMoveContrusctorYTrue)
{
	Engine::Events::MouseMoved event(0, 1);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(posX, 0);
	EXPECT_EQ(posY, 1);
}

TEST(Events, MouseMoveContrusctorYFalse)
{
	Engine::Events::MouseMoved event(0, 1);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(posX, 0);
	EXPECT_NE(posY, 0);
}

TEST(Events, KeyPressedSpaceNoRepeatTrue)
{
	Engine::Events::KeyPressed event(KEY_SPACE, 0);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_EQ(repeat, 0);
}

TEST(Events, KeyPressedSpaceNoRepeatFalse)
{
	Engine::Events::KeyPressed event(KEY_SPACE, 0);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_NE(repeat, 1);
}

TEST(Events, KeyPressedSpaceOneRepeatTrue)
{
	Engine::Events::KeyPressed event(KEY_SPACE, 1);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_EQ(repeat, 1);
}

TEST(Events, KeyPressedSpaceOneRepeatFalse)
{
	Engine::Events::KeyPressed event(KEY_SPACE, 1);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::Events::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_NE(repeat, 0);
}

TEST(Events, DispatchTrue)
{
	Engine::Events::WindowResize event(1920, 1080);
	Engine::Events::EventDispatcher dispatcher(event);
	bool result = dispatcher.dispatch<Engine::Events::WindowResize>(std::bind(onResizeTrue, std::placeholders::_1));
	EXPECT_TRUE(result);
}

TEST(Events, DispatchFalse)
{
	Engine::Events::WindowClose event;
	Engine::Events::EventDispatcher dispatcher(event);
	bool result = dispatcher.dispatch<Engine::Events::WindowResize>(std::bind(onResizeTrue, std::placeholders::_1));
	EXPECT_FALSE(result);
}

TEST(Events, DispatchHandleTrue)
{
	Engine::Events::WindowResize event(1920, 1080);
	Engine::Events::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Engine::Events::WindowResize>(std::bind(onResizeTrue, std::placeholders::_1));
	bool result = event.handled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleFalse)
{
	Engine::Events::WindowResize event(1920, 1080);
	Engine::Events::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Engine::Events::WindowResize>(std::bind(onResizeFalse, std::placeholders::_1));
	bool result = event.handled();
	EXPECT_FALSE(result);
}




