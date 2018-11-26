#pragma once
#include "cocos2d.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"

using namespace cocos2d;

class MouseState : public GlobalNode
{
public:
	static void registerGlobalNode();

	static Vec2 getMousePosition();
	static MouseEvents::MouseEventArgs getMouseState();

private:
	MouseState();
	~MouseState();

	void initializeListeners() override;
	void onMouseMove(EventMouse* event);
	void onMouseDown(EventMouse* event);
	void onMouseUp(EventMouse* event);
	void onMouseScroll();
	void onClickableMouseOverEvent(EventCustom* eventCustom);
	void onClickableMouseOutEvent(EventCustom* eventCustom);
	void onMouseDragEvent(EventCustom* eventCustom);

	static Vec2 mousePosition;
	static bool canClick;
	static bool isDragging;
	static bool isLeftClicked;

	static MouseState* instance;
};

