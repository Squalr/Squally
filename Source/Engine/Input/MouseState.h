#pragma once
#include "cocos2d.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Resources.h"

using namespace cocos2d;

class MouseState : public GlobalNode
{
public:
	static void registerGlobalNode();

	static Vec2 getMousePosition();

private:
	MouseState();
	~MouseState();

	void initializeListeners() override;
	void onMouseMove(EventMouse* event);
	void onMouseDown(EventMouse* event);
	void onMouseUp(EventMouse* event);
	void onClickableMouseOverEvent(EventCustom* eventCustom);
	void onClickableMouseOutEvent(EventCustom* eventCustom);
	void onMouseDragEvent(EventCustom* eventCustom);
	MouseEvents::MouseEventArgs buildArgs();

	static Vec2 mousePosition;
	static bool canClick;
	static bool isDragging;
	static EventMouse::MouseButton mouseButton;

	static MouseState* instance;
};

