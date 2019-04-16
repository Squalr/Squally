#pragma once

#include "Engine/SmartNode.h"

class Card;
class ClickableNode;

class ToggleCard : public SmartNode
{
public:
	static ToggleCard* create();

protected:
	ToggleCard();
	~ToggleCard();

private:
	typedef SmartNode super;
	ClickableNode* upToggle;
	ClickableNode* downToggle;

	Card* activeCard;
};
