#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "Config/ConfigManager.h"
#include "GUI/Mouse.h"
#include "GUI/MenuLabel.h"
#include "GUI/MenuSprite.h"
#include "GUI/Screens/TitleScreen.h"

using namespace cocos2d;

class OptionsMenu : public Scene
{
public:
	static OptionsMenu * create();

protected:
	OptionsMenu();
	~OptionsMenu();

private:
	void onEnter() override;
	void OnMenuClick(MenuLabel* menuLabel);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void InitializeListeners();
	void InitializePositions();

	Mouse* mouse;
	Sprite* background;

	MenuLabel* fullScreenLabel;
	MenuLabel* windowedLabel;
	MenuLabel* exitLabel;

	std::vector<MenuLabel*>* clickableMenus;

	MenuSprite* slider;

	const float titleFontSize = 48.0f;
	const float menuFontSize = 32.0f;
	const float menuOffset = 64.0f;
	const float spacing = -64.0f;
};

