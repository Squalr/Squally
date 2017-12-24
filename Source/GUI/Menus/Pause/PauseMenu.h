#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/MenuBackground.h"
#include "GUI/Menus/Options/OptionsMenu.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/Mouse.h"

using namespace cocos2d;

class PauseMenu : public Scene
{
public:
	static PauseMenu * create();

protected:
	PauseMenu();
	~PauseMenu();

private:
	void onEnter() override;
	void InitializePositions();
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnResumeClick(MenuSprite* menuSprite);
	void OnOptionsClick(MenuSprite* menuSprite);
	void OnExitToTitleClick(MenuSprite* menuSprite);

	MenuBackground* background;
	Sprite* pauseWindow;
	MenuSprite* resumeButton;
	MenuSprite* optionsButton;
	MenuSprite* exitToTitleButton;
};

