#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Hackables/HackableObject.h"
#include "GUI/Menus/Dialog/DialogMenu.h"
#include "GUI/Menus/HackerMode/RadialMenu.h"
#include "GUI/Components/Mouse.h"

using namespace cocos2d;

class HUD : public Node
{
public:
	static HUD * create();

	Layer * hackableObjectsHud;

	void registerHackableObject(HackableObject* hackableObject);

private:
	HUD();
	~HUD();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onDialogOpen(EventCustom* event);

	Sprite* heart;
	Sprite* healthBarFrame;

	RadialMenu* radialMenu;
	Node* dialogNode;
};

