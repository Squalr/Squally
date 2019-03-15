#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"
#include "Engine/UI/UIBoundObject.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class LocalizedLabel;
class LocalizedString;
class UIBoundObject;

class InteractMenu : public SmartNode
{
public:
	static InteractMenu* create(LocalizedString* displayString);

	void show();
	void hide();

protected:
	InteractMenu(LocalizedString* displayString);
	~InteractMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	UIBoundObject* uiElementsBinding;
	cocos2d::Node* uiElements;
	cocos2d::LayerColor* backdrop;
	LocalizedString* displayString;
	LocalizedLabel* displayLabel;
};
