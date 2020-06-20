#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class LocalizedLabel;
class LocalizedString;

class InteractMenu : public SmartNode
{
public:
	static InteractMenu* create(LocalizedString* displayString, cocos2d::Color3B backColor = cocos2d::Color3B::BLACK, float menuWidth = 128.0f);

	void show();
	void hide();

protected:
	InteractMenu(LocalizedString* displayString, cocos2d::Color3B backColor, float menuWidth);
	virtual ~InteractMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;

	void tryRelocate();
	bool isHidden();
	bool isShowing();

	cocos2d::Size menuSize;
	bool hasRelocated;
	bool isFadingIn;
	bool isFadingOut;

	cocos2d::Node* uiElements;
	cocos2d::LayerColor* backdrop;
	LocalizedString* displayString;
	LocalizedLabel* displayLabel;
};
