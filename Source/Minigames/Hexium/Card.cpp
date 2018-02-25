#include "Card.h"

const float Card::cardScale = 0.4f;

Card* Card::create(CardStyle cardStyle, int id)
{
	Card* card = new Card(cardStyle, id);

	card->autorelease();

	return card;
}

Card::Card(CardStyle cardStyle, int id)
{
	this->cardData = CardData::cardList.at(id);

	switch (cardStyle)
	{
	case CardStyle::Shadow:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackShadow);
		break;
	case CardStyle::Robotic:
	default:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackRobotic);
		break;
	}
}

Card::~Card()
{
}

void Card::onEnter()
{
	this->initializePositions();
	this->initializeListeners();
}

void Card::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Card::initializeListeners()
{
}

void Card::reveal()
{

}

void Card::hide()
{

}
