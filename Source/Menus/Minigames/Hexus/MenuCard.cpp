#include "MenuCard.h"

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
	for (auto it = displayItems.begin(); it != displayItems.end(); it++)
	{
		this->removeChild(*it);
	}
}

void MenuCard::initializePositions()
{
	Card::initializePositions();
}

void MenuCard::initializeListeners()
{
	Card::initializeListeners();
}
