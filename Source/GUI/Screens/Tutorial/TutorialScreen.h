#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "TutorialItem.h"
#include "GUI/Mouse.h"
#include "GUI/MenuLabel.h"
#include "GUI/MenuSprite.h"
#include "GUI/Screens/TitleScreen.h"

using namespace cocos2d;

class TutorialScreen : public Scene
{
public:
	TutorialScreen();
	~TutorialScreen();

private:
	void LoadNodes();
	void onEnter() override;
	void InitializeListeners();
	void OnMouseOver(TutorialItem* node);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Mouse* mouse;

	Sprite* background;
	MenuLabel* titleLabel;
	MenuLabel* infoLabel;
	std::vector<MenuSprite*>* tutorialButtons;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;
};

