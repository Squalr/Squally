#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedString;
class LocalizedLabel;
class ClickableNode;

class ConfirmationMenu : public SmartNode
{
public:
	static ConfirmationMenu* create();

	void showMessage(LocalizedString* confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback = nullptr);

private:
	typedef SmartNode super;
	ConfirmationMenu();
	~ConfirmationMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void confirm();
	void close();

	cocos2d::Sprite* confirmWindow;
	LocalizedLabel* confirmationLabel;
	ClickableNode* closeButton;
	ClickableNode* confirmButton;
	ClickableNode* cancelButton;

	std::function<void()> onConfirmCallback;
	std::function<void()> onCancelCallback;
};

