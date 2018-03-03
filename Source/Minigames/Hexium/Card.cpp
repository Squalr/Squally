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
	this->mouseOverCallback = nullptr;
	this->cardData = data;

	switch (cardStyle)
	{
	case CardStyle::Earth:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackEarth);
		this->cardFront = Sprite::create(Resources::Minigames_Hexium_CardFrontEarth);
		break;
	case CardStyle::Water:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackWater);
		this->cardFront = Sprite::create(Resources::Minigames_Hexium_CardFrontWater);
		break;
	case CardStyle::Air:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackAir);
		this->cardFront = Sprite::create(Resources::Minigames_Hexium_CardFrontAir);
		break;
	case CardStyle::Fire:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackFire);
		this->cardFront = Sprite::create(Resources::Minigames_Hexium_CardFrontFire);
		break;
	case CardStyle::Light:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackLight);
		this->cardFront = Sprite::create(Resources::Minigames_Hexium_CardFrontLight);
		break;
	case CardStyle::Shadow:
		this->cardBack = Sprite::create(Resources::Minigames_Hexium_CardBackShadow);
		this->cardFront = Sprite::create(Resources::Minigames_Hexium_CardFrontShadow);
		break;
	}

	this->cardImage = Sprite::create(data->cardResourceFile);
	this->cardSelected = Node::create();
	this->cardSelected->addChild(Sprite::create(data->cardResourceFile));
	this->cardSelected->addChild(Sprite::create(Resources::Minigames_Hexium_CardSelect));
	this->cardSprite = MenuSprite::create(this->cardImage, this->cardSelected, Sprite::create(data->cardResourceFile));

	this->attackFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->attackFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->cardText = Label::create("", Resources::Fonts_UbuntuMono_B, 64.0f);
	this->cardText->setAlignment(TextHAlignment::LEFT);
	this->cardText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->cardImage->setScale(0.9f);
	this->setScale(Card::cardScale);
	this->updateText();

	this->addChild(this->cardBack);
	this->addChild(this->cardFront);
	this->addChild(this->cardSprite);
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
	Size cardSize = this->cardImage->getContentSize() * Card::cardScale;

	this->cardText->setPosition(Vec2(-cardSize.width / 2.0f - 48.0f, cardSize.height / 2.0f + 96.0f));
	this->attackFrame->setPosition(Vec2(-cardSize.width / 2.0f - 64.0f, cardSize.height / 2.0f + 32.0f));
}

void Card::initializeListeners()
{
	this->cardSprite->setMouseOverCallback(CC_CALLBACK_1(Card::onMouseOver, this));
}

void Card::setScale(float scale)
{
	Node::setScale(scale);
	this->cardSprite->setContentScale(scale);

	// Seriously I do not understand why this is needed. Cocos2d-x is pretty shitty when it comes to dealing with scale.
	const Vec2 cardOffsetCorrection = Vec2(28.0f, 36.0f);
	this->cardSprite->setOffsetCorrection(cardOffsetCorrection);
}

int Card::getAttack()
{
	// TODO: Apply transformations here
	return this->cardData->attack;
}

void Card::reveal()
{
	this->cardBack->setVisible(false);
	this->cardFront->setVisible(true);
	this->cardSprite->setVisible(true);
	this->cardText->setVisible(true);
	this->attackFrame->setOpacity(196);
}

void Card::hide()
{
	this->cardBack->setVisible(true);
	this->cardFront->setVisible(false);
	this->cardSprite->setVisible(false);
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
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_SHL:
	case CardData::CardType::Special_SHR:
	case CardData::CardType::Special_INV:
	case CardData::CardType::Special_FLIP1:
	case CardData::CardType::Special_FLIP2:
	case CardData::CardType::Special_FLIP3:
	case CardData::CardType::Special_FLIP4:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
	case CardData::CardType::Special:
		this->cardText->setString(this->cardData->getCardTypeString());
		this->cardText->setTextColor(Card::specialColor);
	}

	this->attackFrame->setContentSize(Size(32.0f + this->cardText->getString().length() * 32.0f, 64.0f));
}

void Card::setMouseOverCallback(std::function<void(Card*)> callback)
{
	this->mouseOverCallback = callback;
}

void Card::onMouseOver(MenuSprite* menuSprite)
{
	if (this->mouseOverCallback != nullptr) {
		this->mouseOverCallback(this);
	}
}
