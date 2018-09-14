#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Resources.h"
#include "Scenes/Menus/HackerMode/RadialMenu.h"

using namespace cocos2d;

class HackerModeHud : public Hud
{
public:
	static HackerModeHud * create(function<void()> toggleHackermodeCallback);

	Layer * hackableObjectsHud;

private:
	HackerModeHud(function<void()> toggleHackermodeCallback);
	~HackerModeHud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onRadialMenuClose();

	void registerHackableObject(EventCustom* args);

	Node* hackableButtonLayer;
	RadialMenu* radialMenu;
	function<void()> callback;
};

