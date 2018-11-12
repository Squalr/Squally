#pragma once
#include "cocos2d.h"


#include "Engine/Localization/Localization.h"
#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/Mouse.h"
#include "Events/NavigationEvents.h"
#include "Resources.h"

using namespace cocos2d;

class ConfirmationMenu : public SmartNode
{
public:
	static ConfirmationMenu * create();

	void initialize(std::string confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback);

private:
	ConfirmationMenu();
	~ConfirmationMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onCloseClick(MenuSprite* menuSprite);
	void onConfirmClick(MenuSprite* menuSprite);
	void onCancelClick(MenuSprite* menuSprite);

	Sprite* pauseWindow;
	Label* confirmationLabel;
	MenuSprite* closeButton;
	MenuSprite* confirmButton;
	MenuSprite* cancelButton;

	std::function<void()> onConfirmCallback;
	std::function<void()> onCancelCallback;
};

