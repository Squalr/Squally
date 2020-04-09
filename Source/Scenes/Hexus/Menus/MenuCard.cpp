#include "MenuCard.h"

using namespace cocos2d;

MenuCard* MenuCard::create(Card::CardStyle cardStyle, CardData* cardData)
{
	MenuCard* instance = new MenuCard(cardStyle, cardData);

	instance->autorelease();

	return instance;
}

MenuCard::MenuCard(Card::CardStyle cardStyle, CardData* cardData) : Card(cardStyle, cardData)
{
	this->displayItems = std::vector<Node*>();
}

MenuCard::~MenuCard()
{
}

void MenuCard::initializePositions()
{
	super::initializePositions();
}

void MenuCard::initializeListeners()
{
	super::initializeListeners();
}

void MenuCard::addDisplayItem(Node* node)
{
	this->addChild(node);
}

void MenuCard::removeDisplayItem(Node* node)
{
	this->removeChild(node);
}

void MenuCard::clearDisplayItems()
{
	for (auto next : displayItems)
	{
		this->removeChild(next);
	}
}
