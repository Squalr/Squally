#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Mouse.h"
#include "GUI/MenuLabel.h"

using namespace cocos2d;

class OptionsMenu : public Scene
{
public:
	OptionsMenu();
	~OptionsMenu();

private:
	void onEnter() override;
	void InitializeListeners();
	void OnMenuClick(MenuLabel* menuLabel);

	void SetFullScreen();
	void SetWindowed();

	Mouse* mouse;
	Sprite* background;

	MenuLabel* titleLabel;
	MenuLabel* fullScreenLabel;
	MenuLabel* windowedLabel;
	MenuLabel* exitLabel;

	std::vector<MenuLabel*>* clickableMenus;

	const float titleFontSize = 48.0f;
	const float menuFontSize = 32.0f;
	const float menuOffset = 64.0f;
	const float spacing = -40.0f;
};

