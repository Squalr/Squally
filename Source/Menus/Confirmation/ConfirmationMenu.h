#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedString;
class LocalizedLabel;
class MenuSprite;

class ConfirmationMenu : public SmartNode
{
public:
	static ConfirmationMenu* create();

	void showMessage(LocalizedString* confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback);

private:
	typedef SmartNode super;
	ConfirmationMenu();
	~ConfirmationMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onCloseClick(MenuSprite* menuSprite);
	void onConfirmClick(MenuSprite* menuSprite);
	void onCancelClick(MenuSprite* menuSprite);

	cocos2d::Sprite* confirmWindow;
	LocalizedLabel* confirmationLabel;
	MenuSprite* closeButton;
	MenuSprite* confirmButton;
	MenuSprite* cancelButton;

	std::function<void()> onConfirmCallback;
	std::function<void()> onCancelCallback;
};

