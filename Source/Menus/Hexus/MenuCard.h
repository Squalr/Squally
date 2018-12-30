#pragma once

#include "Scenes/Hexus/Card.h"

class MenuCard : public Card
{
public:
	static MenuCard* create(Card::CardStyle cardStyle, CardData* cardData);

	void addDisplayItem(cocos2d::Node* node);
	void removeDisplayItem(cocos2d::Node* node);
	void clearDisplayItems();

protected:
	MenuCard(Card::CardStyle cardStyle, CardData* cardData);
	~MenuCard();

private:
	void initializePositions() override;
	void initializeListeners() override;

	std::vector<cocos2d::Node*> displayItems;
};
