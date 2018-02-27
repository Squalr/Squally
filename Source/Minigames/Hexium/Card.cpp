#include "Card.h"

const float Card::cardScale = 0.4f;

Card* Card::create(CardStyle cardStyle, CardData* data)
{
	Card* card = new Card(cardStyle, data);

	card->autorelease();

	return card;
}

Card::Card(CardStyle cardStyle, CardData* data)
{
	this->cardData = data;

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

	this->cardFront = Sprite::create(data->cardResourceFile);

	this->cardBack->setScale(Card::cardScale);
	this->cardFront->setScale(Card::cardScale);

	this->addChild(this->cardBack);
	this->addChild(this->cardFront);
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
