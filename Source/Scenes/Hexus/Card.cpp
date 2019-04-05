#include "Card.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/HackUtils.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardEffects.h"
#include "Scenes/Hexus/Config.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Generics/Constant.h"

using namespace cocos2d;

const float Card::cardScale = 0.4f;
const Color4B Card::binaryColor = Color4B(35, 150, 255, 255);
const Color4B Card::decimalColor = Color4B(255, 255, 255, 255);
const Color4B Card::hexColor = Color4B(78, 149, 66, 255);
const Color4B Card::specialColor = Color4B(255, 116, 0, 255);
const Color4B Card::debuffColor = Color4B(225, 0, 0, 255);
const Color4B Card::buffColor = Color4B(30, 223, 0, 255);

Card* Card::create(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard)
{
	Card* instance = new Card(cardStyle, data, isPlayerOwnedCard);

	instance->autorelease();

	return instance;
}

Card::Card(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard)
{
	this->mouseOverCallback = nullptr;
	this->isPlayerOwnedCard = isPlayerOwnedCard;
	this->operations = std::vector<Operation>();
	this->cardData = data;

	switch (data->cardType)
	{
		case CardData::CardType::Binary:
		{
			this->cardFront = Sprite::create(HexusResources::CardFrontCoverBin);
			break;
		}
		case CardData::CardType::Decimal:
		{
			this->cardFront = Sprite::create(HexusResources::CardFrontCoverDec);
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			this->cardFront = Sprite::create(HexusResources::CardFrontCoverHex);
			break;
		}
		default:
		{
			this->cardFront = Sprite::create(HexusResources::CardFrontCoverSpecial);
			break;
		}
	}

	switch (cardStyle)
	{
		case CardStyle::Water:
		{
			this->cardBack = Sprite::create(HexusResources::CardBackWater);
			break;
		}
		case CardStyle::Air:
		{
			this->cardBack = Sprite::create(HexusResources::CardBackAir);
			break;
		}
		case CardStyle::Fire:
		{
			this->cardBack = Sprite::create(HexusResources::CardBackFire);
			break;
		}
		case CardStyle::Light:
		{
			this->cardBack = Sprite::create(HexusResources::CardBackLight);
			break;
		}
		case CardStyle::Shadow:
		{
			this->cardBack = Sprite::create(HexusResources::CardBackShadow);
			break;
		}
		case CardStyle::Earth:
		default:
		{
			this->cardBack = Sprite::create(HexusResources::CardBackEarth);
			break;
		}
	}

	this->cardSelect = ClickableNode::create(HexusResources::CardUnselected, HexusResources::CardSelect);
	this->cardSelect->setClickSound(SoundResources::Menus_Card_Game_UI_Button_Light_Reverb_02);
	this->cardSprite = Sprite::create(data->cardResourceFile);
	this->cardFocus = Sprite::create(HexusResources::CardSelect);
	this->cardEffects = CardEffects::create();

	this->cardString = ConstantString::create();
	this->cardLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M2, Strings::Generics_Constant::create());

	this->cardLabel->setStringReplacementVariables(this->cardString);
	this->cardLabel->setAlignment(TextHAlignment::CENTER);
	this->cardLabel->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->cardLabel->enableOutline(Color4B::BLACK, 6);

	this->setContentSize(this->cardSelect->getContentSize());
	this->setScale(Card::cardScale);

	this->updateText();

	this->addChild(this->cardBack);
	this->addChild(this->cardSprite);
	this->addChild(this->cardFront);
	this->addChild(this->cardFocus);
	this->addChild(this->cardSelect);
	this->addChild(this->cardEffects);
	this->addChild(this->cardLabel);

	this->hide();
	this->unfocus();
}

Card::~Card()
{
}

void Card::onEnter()
{
	SmartNode::onEnter();
}

void Card::initializePositions()
{
	SmartNode::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cardLabel->setPosition(Vec2(0.0f, -88.0f));
}

void Card::initializeListeners()
{
	SmartNode::initializeListeners();

	this->cardSelect->setMouseOverCallback(CC_CALLBACK_0(Card::onMouseOver, this));
	this->cardSelect->setMouseOutCallback(CC_CALLBACK_0(Card::onMouseOut, this));
	this->cardSelect->setMouseClickCallback(CC_CALLBACK_0(Card::onMouseClick, this));
}

void Card::addOperation(Operation operation)
{
	this->operations.push_back(operation);
	this->updateText();
}

void Card::clearOperations()
{
	this->operations.clear();
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

Card::Operation Card::toOperation(unsigned int immediate)
{
	switch (this->cardData->cardType)
	{
		case CardData::CardType::Special_SHL:
		{
			return Operation(Operation::OperationType::SHL, 1);
		}
		case CardData::CardType::Special_SHR:
		{
			return Operation(Operation::OperationType::SHR, 1);
		}
		case CardData::CardType::Special_FLIP1:
		{
			return Operation(Operation::OperationType::XOR, 0b0001);
		}
		case CardData::CardType::Special_FLIP2:
		{
			return Operation(Operation::OperationType::XOR, 0b0010);
		}
		case CardData::CardType::Special_FLIP3:
		{
			return Operation(Operation::OperationType::XOR, 0b0100);
		}
		case CardData::CardType::Special_FLIP4:
		{
			return Operation(Operation::OperationType::XOR, 0b1000);
		}
		case CardData::CardType::Special_MOV:
		{
			return Operation(Operation::OperationType::MOV, immediate);
		}
		case CardData::CardType::Special_AND:
		{
			return Operation(Operation::OperationType::AND, immediate);
		}
		case CardData::CardType::Special_OR:
		{
			return Operation(Operation::OperationType::OR, immediate);
		}
		case CardData::CardType::Special_XOR:
		{
			return Operation(Operation::OperationType::XOR, immediate);
		}
		case CardData::CardType::Special_ADD:
		{
			return Operation(Operation::OperationType::ADD, immediate);
		}
		case CardData::CardType::Special_SUB:
		{
			return Operation(Operation::OperationType::SUB, immediate);
		}
		case CardData::CardType::Special_NOT:
		{
			return Operation(Operation::OperationType::NOT);
		}
		default:
		{
			return Operation(Operation::OperationType::AND, 0b000);
		}
	}
}

unsigned int Card::getOriginalAttack()
{
	return this->cardData->attack;
}

unsigned int Card::getAttack()
{
	unsigned int attack = this->cardData->attack;

	for (auto it = this->operations.begin(); it != this->operations.end(); it++)
	{
		Operation operation = *it;
		attack = this->applyOperation(attack, operation);
	}

	return attack;
}

void Card::setIsPlayerOwnedCard(bool isPlayerOwnedCard)
{
	this->isPlayerOwnedCard = isPlayerOwnedCard;
}

bool Card::getIsPlayerOwnedCard()
{
	return this->isPlayerOwnedCard;
}

int Card::applyOperation(int attack, Operation operation)
{
	if (this->cardData->cardKey == CardKeys::Absorb)
	{
		return 0b0000;
	}

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
		case Operation::OperationType::NOT:
		{
			attack ^= 0b1111;
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
		{
			break;
		}
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
	this->cardLabel->setVisible(true);
}

void Card::hide()
{
	this->cardBack->setVisible(true);
	this->cardFront->setVisible(false);
	this->cardSprite->setVisible(false);
	this->cardLabel->setVisible(false);
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
		{
			this->cardString->setString(HackUtils::toBinary4(this->getAttack()));
			this->cardLabel->setTextColor(Card::binaryColor);
			break;
		}
		case CardData::CardType::Decimal:
		{
			this->cardString->setString(std::to_string(this->getAttack()));
			this->cardLabel->setTextColor(Card::decimalColor);
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			this->cardString->setString(HackUtils::toHex(this->getAttack()));
			this->cardLabel->setTextColor(Card::hexColor);
			break;
		}
		default:
		{
			this->cardString->setString(this->cardData->getCardTypeString()->getString());
			this->cardLabel->setTextColor(Card::specialColor);
			break;
		}
	}

	if (actualAttack > this->cardData->attack)
	{
		this->cardLabel->setTextColor(Card::buffColor);
	}
	else if (actualAttack < this->cardData->attack)
	{
		this->cardLabel->setTextColor(Card::debuffColor);
	}
}

void Card::setMouseOverCallback(std::function<void(Card*)> callback)
{
	this->mouseOverCallback = callback;
}

void Card::setMouseOutCallback(std::function<void(Card*)> callback)
{
	this->mouseOutCallback = callback;
}

void Card::setMouseClickCallback(std::function<void(Card*)> callback)
{
	this->mouseClickCallback = callback;
}

void Card::onMouseOver()
{
	if (this->mouseOverCallback != nullptr)
	{
		this->mouseOverCallback(this);
	}
}

void Card::onMouseOut()
{
	if (this->mouseOutCallback != nullptr)
	{
		this->mouseOutCallback(this);
	}
}

void Card::onMouseClick()
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
