#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "Config/ConfigManager.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/Slider.h"
#include "GUI/Components/ToggleButton.h"

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
	void OnCloseClick(MenuSprite* menuSprite);
	void OnMouseMove(EventMouse* event);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void InitializeListeners();
	void InitializePositions();

	Mouse* mouse;
	Sprite* background;

	MenuLabel* exitLabel;
	MenuSprite* closeButton;

	Sprite* musicIcon;
	Sprite* soundIcon;
	Slider* musicSlider;
	Slider* soundSlider;
	MenuLabel* fullScreenLabel;
	ToggleButton* fullScreenButton;

	std::vector<MenuSprite*>* clickableMenus;

	const float titleFontSize = 48.0f;
	const float menuFontSize = 32.0f;
	const float menuOffset = 0.0f;
	const float spacing = -64.0f;
};

