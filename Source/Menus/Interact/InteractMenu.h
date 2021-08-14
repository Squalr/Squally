#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
}

class LocalizedLabel;
class LocalizedString;

class InteractMenu : public SmartNode
{
public:
	static InteractMenu* create(LocalizedString* displayString, cocos2d::Color3B backColor = cocos2d::Color3B::BLACK, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO, float minWidth = 128.0f);

	void show();
	void hide();

protected:
	InteractMenu(LocalizedString* displayString, cocos2d::Color3B backColor, cocos2d::Vec2 offset, float minWidth);
	virtual ~InteractMenu();
	
	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void tryRelocate();
	bool isHidden();
	bool isShowing();

	cocos2d::CSize menuSize;
	bool hasRelocated = false;
	bool isFadingIn = false;
	bool isFadingOut = false;

	cocos2d::Node* uiElements = nullptr;
	cocos2d::LayerColor* backdrop = nullptr;
	LocalizedString* displayString = nullptr;
	LocalizedLabel* displayLabel = nullptr;
};
