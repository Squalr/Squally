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
	static TutorialScreen * create();

protected:
	TutorialScreen();
	~TutorialScreen();

private:
	void LoadNodes();
	void onEnter() override;
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Mouse* mouse;

	Sprite* background;
	Sprite* tutorialWindow;
	ParticleSystem* plasma;
	ParticleSystem* swirl;
	ParticleSystem* warp;
	std::vector<MenuSprite*>* tutorialButtons;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;
};

