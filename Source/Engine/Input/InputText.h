#pragma once

#include "cocos/ui/UITextField.h"

#include "Engine/Localization/LocalizedLabel.h"

class ConstantString;
class ClickableNode;

class InputText : public cocos2d::ui::UICCTextField
{
public:
	static InputText* create(cocos2d::Size minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize);

	void setString(const std::string& label) override;
	std::string getFont();
	float getFontSize();
	ClickableNode* getHitbox();

private:
	typedef UICCTextField super;
	InputText(cocos2d::Size minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize);
	virtual ~InputText() = default;

	void onEnter() override;
	void initializePositions();

	ConstantString* labelText;
	LocalizedLabel* inputLabel;
	ClickableNode* hitbox;

	cocos2d::Size minimumInputSize;
};
