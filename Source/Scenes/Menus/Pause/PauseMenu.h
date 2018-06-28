#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/TextMenuSprite.h"
#include "Resources.h"
#include "Scenes/Menus/Confirmation/ConfirmationMenu.h"
#include "Scenes/Menus/MenuBackground.h"
#include "Scenes/Menus/Options/OptionsMenu.h"

using namespace cocos2d;

class PauseMenu : public FadeScene
{
public:
	static PauseMenu * create();

protected:
	PauseMenu();
	~PauseMenu();

private:
	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onExitConfirm();
	void onCloseClick(MenuSprite* menuSprite);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onResumeClick(MenuSprite* menuSprite);
	void onOptionsClick(MenuSprite* menuSprite);
	void onExitClick(MenuSprite* menuSprite);

	Node* background;
	Sprite* pauseWindow;
	Label* titleLabel;
	MenuSprite* closeButton;
	TextMenuSprite* resumeButton;
	TextMenuSprite* optionsButton;
	TextMenuSprite* exitButton;

	static const Color3B TitleColor;
	static const std::string StringKeyMenuPause;
	static const std::string StringKeyResume;
	static const std::string StringKeyOptions;
	static const std::string StringKeyExit;
	static const std::string StringKeyExitPrompt;
};

