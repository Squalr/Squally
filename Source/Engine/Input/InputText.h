#pragma once

#include "cocos/ui/UITextField.h"

#include "Engine/SmartNode.h"

class MenuLabel;

namespace cocos2d
{
}

class ClickableNode;
class LocalizedLabel;

class InputText : public cocos2d::ui::UICCTextField
{
public:
	static InputText* create(LocalizedLabel* referenceLabel);

	std::string getFont();
	float getFontSize();

private:
	typedef UICCTextField super;
	InputText(LocalizedLabel* referenceLabel);
	virtual ~InputText() = default;

	void onEnter() override;
	void update(float dt) override;

	LocalizedLabel* referenceLabel;
	ClickableNode* hitbox;
};
