#pragma once
#include "Engine/Events/MouseEvents.h"
#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class EventCustom;
	class EventMouse;
}

class MouseState : public GlobalNode
{
public:
	static void registerGlobalNode();

	static cocos2d::Vec2 getMousePosition();
	static MouseEvents::MouseEventArgs getMouseState();

private:
	typedef GlobalNode super;
	MouseState();
	virtual ~MouseState();

	void initializeListeners() override;
	void onMouseMove(cocos2d::EventMouse* event);
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseUp(cocos2d::EventMouse* event);
	void onMouseScroll();
	void onClickableMouseOverEvent(cocos2d::EventCustom* eventCustom);
	void onClickableMouseOutEvent(cocos2d::EventCustom* eventCustom);
	void onMouseDragEvent(cocos2d::EventCustom* eventCustom);

	static cocos2d::Vec2 mousePosition;
	static bool canClick;
	static bool isDragging;
	static bool isLeftClicked;

	static MouseState* instance;
};

