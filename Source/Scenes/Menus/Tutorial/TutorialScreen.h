#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/FloatingSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

#include "TutorialScreen.h"
#include "TutorialItem.h"

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
	void initializePositions() override;
	void initializeListeners() override;
	void onCloseClick(MenuSprite* menuSprite);
	void onMouseOver(TutorialItem* tutorialItem);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	int currentPage;

	Sprite* tutorialWindow;
	Label* titleLabel;
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

	static const Color3B TitleColor;
	static const std::string StringKeyMenuTutorials;
};

