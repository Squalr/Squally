#pragma once
#include "cocos2d.h"

#include "Engine/Objects/Hackables/HackableObject.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Resources.h"
#include "Scenes/Menus/HackerMode/RadialMenu.h"

using namespace cocos2d;

class HackerModeHud : public UILayer
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

