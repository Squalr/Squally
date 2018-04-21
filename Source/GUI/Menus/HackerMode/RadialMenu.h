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
	static RadialMenu * create();

private:
	RadialMenu();
	~RadialMenu();

	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onHackableEdit(EventCustom* eventArgs);
	void onClose(MenuSprite* menuSprite);

	CodeMenu* codeMenu;
	DataMenu* dataMenu;

	HackableObject* activeHackableObject;

	LayerColor* layerColor;
	DrawNode* line;
	Node* radialNode;
	MenuSprite* returnButton;

	static const Size maxPreviewSize;
};

