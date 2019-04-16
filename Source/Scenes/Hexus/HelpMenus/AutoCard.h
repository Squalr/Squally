#pragma once

#include "Engine/SmartNode.h"

class Card;
class ClickableNode;

class AutoCard : public SmartNode
{
public:
	static AutoCard* create(int defaultAttack = 5);

	enum class DisplayType
	{
		Binary,
		Decimal,
		Hex
	};

	void incrementAttack();
	void decrementAttack();
	void setAttack(int attack);
	int getAttack();
	void setDisplayType(DisplayType displayType);
	void setCardScale(float cardScale);

	Card* activeCard;

private:
	typedef SmartNode super;
	AutoCard(int defaultAttack);
	~AutoCard();

	void onEnter() override;

	cocos2d::Node* cardNode;
	ClickableNode* upToggle;
	ClickableNode* downToggle;

	void updateToggle();

	DisplayType displayType;
	float cardScale;
	int currentAttack;
};
