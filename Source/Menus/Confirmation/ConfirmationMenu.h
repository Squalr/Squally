#pragma once
#include <functional>

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class LocalizedString;
class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;

class ConfirmationMenu : public Hud
{
public:
	static ConfirmationMenu* create();

	void showMessage(LocalizedString* confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback = nullptr);

	void disableBackdrop();

protected:
	ConfirmationMenu();
	virtual ~ConfirmationMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;
	void confirm();
	void close();

	cocos2d::Sprite* confirmWindow;
	LocalizedLabel* confirmationLabel;
	ClickableNode* closeButton;
	ClickableTextNode* confirmButton;
	ClickableTextNode* cancelButton;
	cocos2d::LayerColor* backdrop;

	std::function<void()> onConfirmCallback;
	std::function<void()> onCancelCallback;
};

