#include "Card.h"

const float Card::cardScale = 0.4f;
const Color4B Card::binaryColor = Color4B(35, 150, 255, 255);
const Color4B Card::decimalColor = Color4B(255, 255, 255, 255);
const Color4B Card::hexColor = Color4B(30, 223, 0, 255);
const Color4B Card::specialColor = Color4B(255, 116, 0, 255);

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
	this->attackFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->attackFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->cardText = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->cardText->setAlignment(TextHAlignment::LEFT);
	this->cardText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->setScale(Card::cardScale);
	this->updateText();

	this->addChild(this->cardBack);
	this->addChild(this->cardFront);
	this->addChild(this->attackFrame);
	this->addChild(this->cardText);

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
	Size cardSize = this->cardFront->getContentSize() * Card::cardScale;

	this->cardText->setPosition(Vec2(-cardSize.width / 2.0f - 48.0f, cardSize.height / 2.0f + 96.0f));
	this->attackFrame->setPosition(Vec2(-cardSize.width / 2.0f - 64.0f, cardSize.height / 2.0f + 48.0f));
}

void Card::initializeListeners()
{
}

void Card::reveal()
{
	this->cardBack->setVisible(false);
	this->cardFront->setVisible(true);
	this->cardText->setVisible(true);
	this->attackFrame->setOpacity(196);
}

void Card::hide()
{
	this->cardBack->setVisible(true);
	this->cardFront->setVisible(false);
	this->cardText->setVisible(false);
	this->attackFrame->setOpacity(0);
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

void Card::updateText()
{
	switch (this->cardData->cardType)
	{
	case CardData::CardType::Binary:
		this->cardText->setString(HackUtils::toBinary4(this->cardData->attack));
		this->cardText->setTextColor(Card::binaryColor);
		break;
	case CardData::CardType::Decimal:
		this->cardText->setString(std::to_string(this->cardData->attack));
		this->cardText->setTextColor(Card::decimalColor);
		break;
	case CardData::CardType::Hexidecimal:
		this->cardText->setString(HackUtils::toHex(this->cardData->attack));
		this->cardText->setTextColor(Card::hexColor);
		break;
	case CardData::CardType::Special_AND:
		this->cardText->setString("AND");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_OR:
		this->cardText->setString("OR");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_XOR:
		this->cardText->setString("XOR");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_SHL:
		this->cardText->setString("SHL");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_SHR:
		this->cardText->setString("SHR");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_INV:
		this->cardText->setString("INV");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_FLIP1:
		this->cardText->setString("FLIP1");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_FLIP2:
		this->cardText->setString("FLIP2");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_FLIP3:
		this->cardText->setString("FLIP3");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_FLIP4:
		this->cardText->setString("FLIP4");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_ADD:
		this->cardText->setString("ADD");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special_SUB:
		this->cardText->setString("SUB");
		this->cardText->setTextColor(Card::specialColor);
		break;
	case CardData::CardType::Special:
		this->cardText->setString("???");
		this->cardText->setTextColor(Card::specialColor);
		break;
	}

	this->attackFrame->setContentSize(Size(32.0f + this->cardText->getString().length() * 24.0f, 48.0f));
}
