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

	this->setScale(Card::cardScale);

	this->addChild(this->cardBack);
	this->addChild(this->cardFront);

	this->hide();
}

Card::~Card()
{
}

void Card::onEnter()
{
	Node::onEnter();

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
	this->cardBack->setVisible(false);
	this->cardFront->setVisible(true);
}

void Card::hide()
{
	this->cardBack->setVisible(true);
	this->cardFront->setVisible(false);
}

void Card::doDrawAnimation(float cardDrawDelay)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->reveal();

	this->runAction(
		EaseSineInOut::create(MoveTo::create(cardDrawDelay, Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f)))
	);

	this->runAction(
		ScaleTo::create(cardDrawDelay, 1.0f)
	);
}
