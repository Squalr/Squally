#pragma once

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class EventCustom;
	class EventMouse;
}

struct MouseEventArgs;

class MouseState : public GlobalNode
{
public:
	static void registerGlobalNode();

	static cocos2d::Vec2 getMousePosition();
	static MouseEventArgs getMouseState();

private:
	typedef GlobalNode super;
	MouseState();
	virtual ~MouseState();

	void initializeListeners() override;
	void onMouseMove(cocos2d::EventMouse* event);
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseUp(cocos2d::EventMouse* event);
	void onMouseScroll(cocos2d::EventMouse* event);
	void onEventClickableMouseOver(cocos2d::EventCustom* eventCustom);
	void onEventClickableMouseOut(cocos2d::EventCustom* eventCustom);
	void onEventMouseDrag(cocos2d::EventCustom* eventCustom);

	static cocos2d::Vec2 mouseInitialPosition;
	static cocos2d::Vec2 mousePosition;
	static cocos2d::Vec2 scrollDelta;
	static bool canClick;
	static bool isDragging;
	static bool isLeftClicked;

	static MouseState* instance;
};

