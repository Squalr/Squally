#pragma once
#include "cocos2d.h"

#include "Events/DialogEvents.h"
#include "Engine/Objects/Hackables/HackableObject.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Resources.h"
#include "Scenes/Menus/Dialog/DialogMenu.h"
#include "Scenes/Menus/HackerMode/RadialMenu.h"

using namespace cocos2d;

class Hud : public UILayer
{
public:
	static Hud * create();

private:
	Hud();
	~Hud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onDialogOpen(EventCustom* event);

	Sprite* heart;
	Sprite* healthBarFrame;

	Node* dialogNode;
};
