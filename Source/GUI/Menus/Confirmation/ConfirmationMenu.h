#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/MenuBackground.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/Mouse.h"

using namespace cocos2d;

class ConfirmationMenu : public FadeScene
{
public:
	static ConfirmationMenu * create();

protected:
	ConfirmationMenu();
	~ConfirmationMenu();

private:
	void onEnter() override;
	void InitializePositions();
	void InitializeListeners();
	void OnCloseClick(MenuSprite* menuSprite);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnResumeClick(MenuSprite* menuSprite);
	void OnOptionsClick(MenuSprite* menuSprite);
	void OnExitToTitleClick(MenuSprite* menuSprite);

	Node* background;
	Sprite* pauseWindow;
	MenuSprite* closeButton;
	MenuSprite* resumeButton;
	MenuSprite* optionsButton;
	MenuSprite* exitToTitleButton;
};

