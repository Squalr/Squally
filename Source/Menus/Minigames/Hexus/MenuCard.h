#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Scenes/Hexus/Card.h"

using namespace cocos2d;

class MenuCard : public Card
{
public:
	static MenuCard * create(Card::CardStyle cardStyle, CardData* cardData);

	void addDisplayItem(Node* node);
	void removeDisplayItem(Node* node);
	void clearDisplayItems();

protected:
	MenuCard(Card::CardStyle cardStyle, CardData* cardData);
	~MenuCard();

private:
	void initializePositions() override;
	void initializeListeners() override;

	std::vector<Node*> displayItems;
};
