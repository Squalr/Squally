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
	static ConfirmationMenu * create(std::string confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback);

protected:
	ConfirmationMenu(std::string confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback);
	~ConfirmationMenu();

private:
	void onEnter() override;
	void InitializePositions();
	void OnCloseClick(MenuSprite* menuSprite);
	void OnConfirmClick(MenuSprite* menuSprite);
	void OnCancelClick(MenuSprite* menuSprite);

	Node* background;
	Sprite* pauseWindow;
	Label* confirmationLabel;
	MenuSprite* closeButton;
	MenuSprite* confirmButton;
	MenuSprite* cancelButton;

	std::function<void()> onConfirmCallback;
	std::function<void()> onCancelCallback;
};

