#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Shaders/PostProcess.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Menus/HackerMode/CodeMenu.h"
#include "GUI/Menus/HackerMode/DataMenu.h"
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

	CodeEditor* codeEditor;
	DataMenu* dataMenu;

	HackableObject* activeHackableObject;

	LayerColor* layerColor;
	Node* radialNode;
	MenuSprite* returnButton;

	std::function<void()> onRadialMenuCloseCallback;

	static const int radialMenuRadius;
	static const Size maxPreviewSize;
};

