#pragma once

#include "Engine/SmartNode.h"

class MenuLabel;

namespace cocos2d
{
	namespace ui
	{
		class UICCTextField;
	}
}

class ClickableNode;
class LocalizedLabel;

class InputText : public SmartNode
{
public:
	static InputText* create(LocalizedLabel* referenceContentLabel);

private:
	typedef SmartNode super;
	InputText(LocalizedLabel* referenceContentLabel);
	virtual ~InputText() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::ui::UICCTextField* editableText;
	ClickableNode* hitbox;
};
