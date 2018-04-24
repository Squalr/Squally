#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Menus/HackerMode/CodeEditor.h"
#include "Objects/Hackables/HackableObject.h"
#include "Utils/HackUtils.h"
#include "Events/HackableEvents.h"

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

	DrawNode* createRadialNode(std::string iconResource, Vec2 position, Color4F color, std::function<void(MenuSprite*, EventMouse* args)> callback, int tag);
	DrawNode* createLineBetweenNodes(Vec2 nodeAPosition, Vec2 nodeBPosition, Color4F color);

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

