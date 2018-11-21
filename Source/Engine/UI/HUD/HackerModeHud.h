#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Menus/HackerMode/RadialMenu.h"
#include "Resources.h"

using namespace cocos2d;

class HackerModeHud : public Hud
{
public:
	static HackerModeHud * create(std::function<void()> toggleHackermodeCallback);

	Layer * hackableObjectsHud;

private:
	HackerModeHud(std::function<void()> toggleHackermodeCallback);
	~HackerModeHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onRadialMenuClose();
	void registerHackableObject(EventCustom* args);

	Node* hackableButtonLayer;
	RadialMenu* radialMenu;
	std::function<void()> callback;
};

