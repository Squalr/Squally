#pragma once

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/UITextField.h"

class ConstantString;
class ClickableNode;

class InputText : public UICCTextField
{
public:
	static InputText* create(cocos2d::CSize minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize, bool unfuck = false);

	void focus();
	void unfocus();
	void setString(const std::string& label) override;
	void setStringChangeCallback(std::function<void(std::string)> stringChangeCallback);
	std::string getFont();
	float getFontSize();
	ClickableNode* getHitbox();

private:
	typedef UICCTextField super;
	InputText(cocos2d::CSize minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize, bool unfuck = false);
	virtual ~InputText();

	void onEnter() override;
	void update(float dt) override;
	void onLocaleChange();
	void initializePositions();
	void initializeListeners();
	cocos2d::CSize resize();

	// This is a hacky fix to some weird scenario where the position changes when there is input in the textfield
	bool unfuck = false;
	std::string stringCache;
	ConstantString* labelText = nullptr;
	LocalizedLabel* inputLabel = nullptr;
	ClickableNode* hitBox = nullptr;
	std::function<void(std::string)> stringChangeCallback = nullptr;

	cocos2d::Vec2 initCoords;
	cocos2d::CSize minimumInputSize;
};
