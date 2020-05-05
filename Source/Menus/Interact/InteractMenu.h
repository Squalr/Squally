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
	static InteractMenu* create(LocalizedString* displayString, float menuWidth = 128.0f);

	void show();
	void hide();

protected:
	InteractMenu(LocalizedString* displayString, float menuWidth);
	virtual ~InteractMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Size menuSize;
	bool hasRelocated;

	cocos2d::Node* uiElements;
	cocos2d::LayerColor* backdrop;
	LocalizedString* displayString;
	LocalizedLabel* displayLabel;
};
