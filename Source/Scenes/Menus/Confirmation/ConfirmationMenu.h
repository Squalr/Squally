#pragma once
#include "cocos2d.h"


#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Resources.h"
#include "Scenes/Menus/MenuBackground.h"

using namespace cocos2d;

class ConfirmationMenu : public FadeScene
{
public:
	static ConfirmationMenu * create();

	void initialize(std::string confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback);

private:
	ConfirmationMenu();
	~ConfirmationMenu();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onCloseClick(MenuSprite* menuSprite);
	void onConfirmClick(MenuSprite* menuSprite);
	void onCancelClick(MenuSprite* menuSprite);

	Node* background;
	Sprite* pauseWindow;
	Label* confirmationLabel;
	MenuSprite* closeButton;
	MenuSprite* confirmButton;
	MenuSprite* cancelButton;

	std::function<void()> onConfirmCallback;
	std::function<void()> onCancelCallback;
};

