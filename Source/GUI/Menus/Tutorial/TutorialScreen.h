#pragma once
#include "cocos2d.h"
#include "TutorialScreen.h"
#include "Resources.h"
#include "GUI/Menus/Tutorial/TutorialItem.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/FloatingSprite.h"

using namespace cocos2d;

class TutorialScreen : public FadeScene
{
public:
	static TutorialScreen * create();

protected:
	TutorialScreen();
	~TutorialScreen();

private:
	void loadLevels();
	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onCloseClick(MenuSprite* menuSprite);
	void onMouseOver(TutorialItem* tutorialItem);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	int currentPage;

	Sprite* tutorialWindow;
	Sprite* descriptionBox;
	Label* description;
	MenuSprite* closeButton;

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

	std::vector<TutorialItem*>* tutorialButtons;

	const float titleFontSize = 48.0f;
	const float infoFontSize = 32.0f;
};

