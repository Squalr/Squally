#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Hackables/HackableObject.h"
#include "Events/DialogEvents.h"
#include "Scenes/Menus/Dialog/DialogMenu.h"
#include "Scenes/Menus/HackerMode/RadialMenu.h"
#include "Engine/Rendering/Components/Mouse.h"

using namespace cocos2d;

class DeveloperHud : public Node
{
public:
	static DeveloperHud * create();

private:
	DeveloperHud();
	~DeveloperHud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};
