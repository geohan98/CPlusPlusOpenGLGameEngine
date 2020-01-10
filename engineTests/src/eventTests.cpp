#include "eventTests.h"

TEST(Events, ResizeConstructorTrue)
{
	Engine::WindowResize event(1920, 1080);
	int width = event.getWidth();
	int height = event.getHeight();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(width, 1920);
	EXPECT_EQ(height, 1080);
}

TEST(Events, ResizeConstructorFalse)
{
	Engine::WindowResize event(1920, 1080);
	int width = event.getWidth();
	int height = event.getHeight();
	Engine::EventType type = event.getEventType();
	EXPECT_NE(width, 192);
	EXPECT_NE(height, 108);
}

TEST(Events, MouseMoveContrusctorXTrue)
{
	Engine::MouseMoved event(1, 0);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(posX, 1);
	EXPECT_EQ(posY, 0);
}

TEST(Events, MouseMoveContrusctorXFalse)
{
	Engine::MouseMoved event(1, 0);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::EventType type = event.getEventType();
	EXPECT_NE(posX, 0);
	EXPECT_EQ(posY, 0);
}


TEST(Events, MouseMoveContrusctorYTrue)
{
	Engine::MouseMoved event(0, 1);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(posX, 0);
	EXPECT_EQ(posY, 1);
}

TEST(Events, MouseMoveContrusctorYFalse)
{
	Engine::MouseMoved event(0, 1);
	int posX = event.getxPos();
	int posY = event.getyPos();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(posX, 0);
	EXPECT_NE(posY, 0);
}

TEST(Events, KeyPressedSpaceNoRepeatTrue)
{
	Engine::KeyPressed event(KEY_SPACE, 0);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_EQ(repeat, 0);
}

TEST(Events, KeyPressedSpaceNoRepeatFalse)
{
	Engine::KeyPressed event(KEY_SPACE, 0);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_NE(repeat, 1);
}

TEST(Events, KeyPressedSpaceOneRepeatTrue)
{
	Engine::KeyPressed event(KEY_SPACE, 1);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_EQ(repeat, 1);
}

TEST(Events, KeyPressedSpaceOneRepeatFalse)
{
	Engine::KeyPressed event(KEY_SPACE, 1);
	unsigned int key = event.getButton();
	int repeat = event.getRepeatCount();
	Engine::EventType type = event.getEventType();
	EXPECT_EQ(key, KEY_SPACE);
	EXPECT_NE(repeat, 0);
}

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

TEST(Events, DispatchHandleTrue)
{
	Engine::WindowResize event(1920, 1080);
	Engine::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Engine::WindowResize>(std::bind(onResizeTrue, std::placeholders::_1));
	bool result = event.handled();
	EXPECT_TRUE(result);
}

TEST(Events, DispatchHandleFalse)
{
	Engine::WindowResize event(1920, 1080);
	Engine::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Engine::WindowResize>(std::bind(onResizeFalse, std::placeholders::_1));
	bool result = event.handled();
	EXPECT_FALSE(result);
}




