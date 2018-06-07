#pragma once
#include "cocos2d.h"

#include "Objects/Hackables/HackableObject.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Resources.h"
#include "Scenes/Menus/HackerMode/RadialMenu.h"

using namespace cocos2d;

class HackerModeHud : public Node
{
public:
	static HackerModeHud * create();

	Layer * hackableObjectsHud;

private:
	HackerModeHud();
	~HackerModeHud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onRadialMenuClose();

	void registerHackableObject(EventCustom* args);

	RadialMenu* radialMenu;
};

