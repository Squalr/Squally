#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "TutorialItem.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/FloatingSprite.h"
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

	FloatingSprite* floatingBox1;
	FloatingSprite* floatingBox2;
	FloatingSprite* floatingBox3;
	FloatingSprite* floatingMisc1;
	FloatingSprite* floatingMisc2;
	FloatingSprite* floatingMisc3;
	FloatingSprite* floatingObelisk1;
	FloatingSprite* floatingObeliskParent;
	FloatingSprite* floatingObeliskChild1;
	FloatingSprite* floatingObeliskChild2;
	FloatingSprite* floatingObeliskChild3;
	FloatingSprite* floatingObeliskChild4;
	FloatingSprite* floatingRocks2;

	ParticleSystem* nether;
	ParticleSystem* swirl;

	std::vector<MenuSprite*>* tutorialButtons;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;
};

