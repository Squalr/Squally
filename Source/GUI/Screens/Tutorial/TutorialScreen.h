#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "TutorialItem.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
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
	void InitializeMovement();
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Mouse* mouse;

	Sprite* background;
	Sprite* tutorialWindow;

	Sprite* floatingBox1;
	Sprite* floatingBox2;
	Sprite* floatingMisc1;
	Sprite* floatingMisc2;
	Sprite* floatingMisc3;
	Sprite* floatingObelisk1;
	Sprite* floatingObeliskParent;
	Sprite* floatingObeliskChild1;
	Sprite* floatingObeliskChild2;
	Sprite* floatingObeliskChild3;
	Sprite* floatingObeliskChild4;
	Sprite* floatingRocks2;

	ParticleSystem* nether;
	ParticleSystem* swirl;

	std::vector<MenuSprite*>* tutorialButtons;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;
};

