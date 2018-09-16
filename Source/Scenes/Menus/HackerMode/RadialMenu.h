#pragma once
#include "cocos2d.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/HackUtils.h"
#include "Engine/Shaders/PostProcess.h"
#include "Events/HackableEvents.h"
#include "Resources.h"

#include "CodeEditor.h"

using namespace cocos2d;

class RadialMenu : public Node
{
public:
	static RadialMenu * create(std::function<void()> onCloseCallback);

private:
	RadialMenu(std::function<void()> onCloseCallback);
	~RadialMenu();

	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onHackableEdit(EventCustom* eventArgs);
	void onHackableAttributeClick(MenuSprite* menuSprite);
	void onClose(MenuSprite* menuSprite);
	void close();

	Node* createRadialNode(std::string iconResource, Vec2 nodePosition, Color4F color, std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> callback, int tag);

	CodeEditor* codeEditor;

	HackableObject* activeHackableObject;

	LayerColor* layerColor;
	Node* radialMenuItems;

	std::function<void()> onRadialMenuCloseCallback;

	static const float radialMenuRadius;
	static const float lineWidth;
	static const Color4F dataColor;
	static const Color4F codeColor;
	static const float iconRadius;
};

