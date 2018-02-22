#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Hackables/HackableObject.h"
#include "GUI/Menus/HackerMode/RadialMenu.h"
#include "GUI/Components/Mouse.h"

using namespace cocos2d;

class HackerModeHud : public Node
{
public:
	static HackerModeHud * create();

	Layer * hackableObjectsHud;

	void registerHackableObject(HackableObject* hackableObject);

private:
	HackerModeHud();
	~HackerModeHud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	RadialMenu* radialMenu;
};

