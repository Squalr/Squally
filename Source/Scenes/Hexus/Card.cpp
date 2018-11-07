#include "Card.h"

const float Card::cardScale = 0.4f;
const Color4B Card::binaryColor = Color4B(35, 150, 255, 255);
const Color4B Card::decimalColor = Color4B(255, 255, 255, 255);
const Color4B Card::hexColor = Color4B(78, 149, 66, 255);
const Color4B Card::specialColor = Color4B(255, 116, 0, 255);
const Color4B Card::debuffColor = Color4B(225, 0, 0, 255);
const Color4B Card::buffColor = Color4B(30, 223, 0, 255);

Card* Card::create(CardStyle cardStyle, CardData* data)
{
	Card* instance = new Card(cardStyle, data);

	instance->autorelease();

	return instance;
}

Card::Card(CardStyle cardStyle, CardData* data)
{
	this->mouseOverCallback = nullptr;
	this->operations = new std::vector<Operation>();
	this->cardData = data;

	switch (data->cardType)
	{
		case CardData::CardType::Binary:
			this->cardFront = Sprite::create(Resources::Minigames_Hexus_CardFrontCoverBin);
			break;
		case CardData::CardType::Decimal:
			this->cardFront = Sprite::create(Resources::Minigames_Hexus_CardFrontCoverDec);
			break;
		case CardData::CardType::Hexidecimal:
			this->cardFront = Sprite::create(Resources::Minigames_Hexus_CardFrontCoverHex);
			break;
		default:
			this->cardFront = Sprite::create(Resources::Minigames_Hexus_CardFrontCoverSpecial);
			break;
	}

	switch (cardStyle)
	{
		default:
		case CardStyle::Earth:
			this->cardBack = Sprite::create(Resources::Minigames_Hexus_CardBackEarth);
			break;
		case CardStyle::Water:
			this->cardBack = Sprite::create(Resources::Minigames_Hexus_CardBackWater);
			break;
		case CardStyle::Air:
			this->cardBack = Sprite::create(Resources::Minigames_Hexus_CardBackAir);
			break;
		case CardStyle::Fire:
			this->cardBack = Sprite::create(Resources::Minigames_Hexus_CardBackFire);
			break;
		case CardStyle::Light:
			this->cardBack = Sprite::create(Resources::Minigames_Hexus_CardBackLight);
			break;
		case CardStyle::Shadow:
			this->cardBack = Sprite::create(Resources::Minigames_Hexus_CardBackShadow);
			break;
	}

	this->cardSelect = MenuSprite::create(Resources::Minigames_Hexus_CardUnselected, Resources::Minigames_Hexus_CardSelect);
	this->cardSelect->setClickSound(Resources::Sounds_Menus_Card_Game_UI_Button_Light_Reverb_02);
	this->cardSprite = Sprite::create(data->cardResourceFile);
	this->cardFocus = Sprite::create(Resources::Minigames_Hexus_CardSelect);

	this->cardText = Label::create("", Localization::getCodingFont(), 64.0f);
	this->cardText->setAlignment(TextHAlignment::CENTER);
	this->cardText->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->cardText->enableOutline(Color4B::BLACK, 6);

	this->setScale(Card::cardScale);
	this->updateText();

	this->addChild(this->cardBack);
	this->addChild(this->cardSprite);
	this->addChild(this->cardFront);
	this->addChild(this->cardFocus);
	this->addChild(this->cardSelect);
	this->addChild(this->cardText);

	this->hide();
	this->unfocus();
}

Card::~Card()
{
	delete(this->operations);
}

void Card::initializePositions()
{
	SmartNode::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cardText->setPosition(Vec2(0.0f, -88.0f));
}

void Card::initializeListeners()
{
	SmartNode::initializeListeners();

	this->cardSelect->setMouseOverCallback(CC_CALLBACK_1(Card::onMouseOver, this));
	this->cardSelect->setClickCallback(CC_CALLBACK_1(Card::onMouseClick, this));
}

void Card::addOperation(Operation operation)
{
	this->operations->push_back(operation);
	this->updateText();
}

void Card::disableInteraction()
{
	this->cardSelect->disableInteraction();
}

void Card::enableInteraction()
{
	this->cardSelect->enableInteraction();
}

void Card::setScale(float scale)
{
	SmartNode::setScale(scale);
	this->cardSelect->setContentScale(scale);

	// Seriously I do not understand why this is needed. Cocos2d-x is pretty shitty when it comes to dealing with scale.
	const Vec2 cardOffsetCorrection = Vec2(28.0f, 36.0f);
	this->cardSelect->setOffsetCorrection(cardOffsetCorrection);
}

Card::Operation Card::toOperation(CardData::CardType playedCardType, unsigned int immediate)
{
	switch (playedCardType)
	{
		case CardData::CardType::Special_SHL:
			return Operation(Operation::OperationType::SHL, 1);
		case CardData::CardType::Special_SHR:
			return Operation(Operation::OperationType::SHR, 1);
		case CardData::CardType::Special_FLIP1:
			return Operation(Operation::OperationType::XOR, 0b0001);
		case CardData::CardType::Special_FLIP2:
			return Operation(Operation::OperationType::XOR, 0b0010);
		case CardData::CardType::Special_FLIP3:
			return Operation(Operation::OperationType::XOR, 0b0100);
		case CardData::CardType::Special_FLIP4:
			return Operation(Operation::OperationType::XOR, 0b1000);
		case CardData::CardType::Special_MOV:
			return Operation(Operation::OperationType::MOV, immediate);
		case CardData::CardType::Special_AND:
			return Operation(Operation::OperationType::AND, immediate);
		case CardData::CardType::Special_OR:
			return Operation(Operation::OperationType::OR, immediate);
		case CardData::CardType::Special_XOR:
			return Operation(Operation::OperationType::XOR, immediate);
		case CardData::CardType::Special_ADD:
			return Operation(Operation::OperationType::ADD, immediate);
		case CardData::CardType::Special_SUB:
			return Operation(Operation::OperationType::SUB, immediate);
		case CardData::CardType::Special_INV:
			return Operation(Operation::OperationType::XOR, 0b1111);
		default:
			return Operation(Operation::OperationType::AND, 0b000);
	}
}

unsigned int Card::getAttack()
{
	unsigned int attack = this->cardData->attack;

	for (auto it = this->operations->begin(); it != this->operations->end(); it++)
	{
		Operation operation = *it;
		attack = this->applyOperation(attack, operation);
	}

	return attack;
}

int Card::applyOperation(int attack, Operation operation) {
	const unsigned int attackMask = 0b1111;

	switch (operation.operationType)
	{
		case Operation::OperationType::SHL:
		{
			attack <<= operation.immediate;
			break;
		}
		case Operation::OperationType::SHR:
		{
			attack >>= operation.immediate;
			break;
		}
		case Operation::OperationType::MOV:
		{
			attack = operation.immediate;
			break;
		}
		case Operation::OperationType::AND:
		{
			attack &= operation.immediate;
			break;
		}
		case Operation::OperationType::OR:
		{
			attack |= operation.immediate;
			break;
		}
		case Operation::OperationType::XOR:
		{
			attack ^= operation.immediate;
			break;
		}
		case Operation::OperationType::ADD:
		{
			attack += operation.immediate;
			break;
		}
		case Operation::OperationType::SUB:
		{
			attack -= operation.immediate;

			if (attack < 0)
			{
				attack = 16 - abs(attack);
			}

			break;
		}
		default:
			break;
	}

	// Ensure only as many as the first 4 bits are set
	attack &= attackMask;

	return attack;
}

void Card::reveal()
{
	this->cardBack->setVisible(true);
	this->cardFront->setVisible(true);
	this->cardSprite->setVisible(true);
	this->cardText->setVisible(true);
}

void Card::hide()
{
	this->cardBack->setVisible(true);
	this->cardFront->setVisible(false);
	this->cardSprite->setVisible(false);
	this->cardText->setVisible(false);
}

void Card::focus()
{
	this->cardFocus->setOpacity(196);
}

void Card::unfocus()
{
	this->cardFocus->setOpacity(0);
	this->cardFocus->setColor(Color3B::WHITE);
}

void Card::setFocusTint(Color3B color)
{
	this->cardFocus->setColor(color);
}

void Card::doDrawAnimation(float cardDrawDelay)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->reveal();

	this->runAction(
		EaseSineInOut::create(MoveTo::create(cardDrawDelay, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f)))
	);

	this->runAction(
		ScaleTo::create(cardDrawDelay, 1.0f)
	);
}

void Card::updateText()
{
	unsigned int actualAttack = this->getAttack();

	switch (this->cardData->cardType)
	{
		case CardData::CardType::Binary:
			this->cardText->setString(HackUtils::toBinary4(this->getAttack()));
			this->cardText->setTextColor(Card::binaryColor);
			break;
		case CardData::CardType::Decimal:
			this->cardText->setString(std::to_string(this->getAttack()));
			this->cardText->setTextColor(Card::decimalColor);
			break;
		case CardData::CardType::Hexidecimal:
			this->cardText->setString(HackUtils::toHex(this->getAttack()));
			this->cardText->setTextColor(Card::hexColor);
			break;
		case CardData::CardType::Special_MOV:
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
			this->cardText->setString(this->cardData->getCardTypeString());
			this->cardText->setTextColor(Card::specialColor);
		default:
			break;
	}

	if (actualAttack > this->cardData->attack)
	{
		this->cardText->setTextColor(Card::buffColor);
	}
	else if (actualAttack < this->cardData->attack)
	{
		this->cardText->setTextColor(Card::debuffColor);
	}
}

void Card::setMouseOverCallback(std::function<void(Card*)> callback)
{
	this->mouseOverCallback = callback;
}

void Card::setMouseClickCallback(std::function<void(Card*)> callback)
{
	this->mouseClickCallback = callback;
}

void Card::onMouseOver(MenuSprite* menuSprite)
{
	if (this->mouseOverCallback != nullptr)
	{
		this->mouseOverCallback(this);
	}
}

void Card::onMouseClick(MenuSprite* menuSprite)
{
	if (this->mouseClickCallback != nullptr)
	{
		this->mouseClickCallback(this);
	}
}

int Card::simulateOperation(Operation operation) 
{
	int attack = this->getAttack();

	return this->applyOperation(attack, operation);
}