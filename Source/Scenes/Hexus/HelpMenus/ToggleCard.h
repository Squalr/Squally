#pragma once

#include "Engine/SmartNode.h"

class AutoCard;
class ClickableNode;

class ToggleCard : public SmartNode
{
public:
	static ToggleCard* create();

	AutoCard* autoCard;

private:
	typedef SmartNode super;
	ToggleCard();
	~ToggleCard();

	void onEnter() override;

	ClickableNode* upToggle;
	ClickableNode* downToggle;
};
