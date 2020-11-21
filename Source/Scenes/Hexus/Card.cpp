#include "Card.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/HackUtils.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardEffects.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float Card::cardScale = 0.4f;
const Color4B Card::BinaryColor = Color4B(35, 150, 255, 255);
const Color4B Card::DecimalColor = Color4B(255, 255, 255, 255);
const Color4B Card::HexColor = Color4B(78, 149, 66, 255);
const Color4B Card::SpecialColor = Color4B(255, 116, 0, 255);
const Color4B Card::DebuffColor = Color4B(225, 0, 0, 255);
const Color4B Card::BuffColor = Color4B(30, 223, 0, 255);

Card* Card::create(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard, bool relocateUI)
{
	Card* instance = new Card(cardStyle, data, isPlayerOwnedCard, relocateUI);

	instance->autorelease();

	return instance;
}

Card::Card(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard, bool relocateUI)
{
	this->mouseOverCallback = nullptr;
	this->isPlayerOwnedCard = isPlayerOwnedCard;
	this->relocateUI = relocateUI;
	this->operations = std::vector<Operation>();
	this->cardData = data;
	this->cardStyle = cardStyle;

	switch (data->getCardType())
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
	this->cardSelect->setClickSound(SoundResources::Menus_ButtonClick4);
	this->cardSprite = Sprite::create(data->getCardResourceFile());
	this->cardFocus = Sprite::create(HexusResources::CardSelect);
	this->cardEffects = CardEffects::create();

	this->cardString = ConstantString::create();
	this->cardLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M2, this->cardString);
	this->overflowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Hexus_Cards_Effects_Overflow::create());
	this->underflowLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Hexus_Cards_Effects_Underflow::create());

	this->overflowLabel->enableOutline(Color4B::BLACK, 4);
	this->underflowLabel->enableOutline(Color4B::BLACK, 4);
	this->overflowLabel->setTextColor(Color4B::RED);
	this->underflowLabel->setTextColor(Color4B::GREEN);
	this->overflowLabel->setOpacity(0);
	this->underflowLabel->setOpacity(0);

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
	this->addChild(this->overflowLabel);
	this->addChild(this->underflowLabel);

	this->hide();
	this->unfocus();
}

Card::~Card()
{
}

Card* Card::clone(bool relocateUI)
{
	Card* card = Card::create(this->cardStyle, this->cardData, this->isPlayerOwnedCard, relocateUI);
	
	if (!this->cardBack->isVisible())
	{
		card->reveal();
	}
	else
	{
		card->hide();
	}

	return card;
}

void Card::onEnter()
{
	super::onEnter();

	this->overflowLabel->setOpacity(0);
	this->underflowLabel->setOpacity(0);
}

void Card::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	if (this->relocateUI)
	{
		// TODO: This is broken somehow, there is an issue where these are not being properly positioned as UIBoundObjects
		// ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->overflowLabel));
		// ObjectEvents::TriggerBindObjectToUI(RelocateObjectArgs(this->underflowLabel));
	}
}

void Card::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cardLabel->setPosition(Vec2(0.0f, -88.0f));
}

void Card::initializeListeners()
{
	super::initializeListeners();

	this->cardSelect->setMouseOverCallback([=](InputEvents::MouseEventArgs* args){ this->onMouseOver(); });
	this->cardSelect->setMouseOutCallback([=](InputEvents::MouseEventArgs* args){ this->onMouseOut(); });
	this->cardSelect->setMouseClickCallback([=](InputEvents::MouseEventArgs* args){ this->onMouseClick(); });
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
	switch (this->cardData->getCardType())
	{
		case CardData::CardType::Special_SHL:
		{
			return Operation(Operation::OperationType::SHL, 0b0001);
		}
		case CardData::CardType::Special_SHR:
		{
			return Operation(Operation::OperationType::SHR, 0b0001);
		}
		case CardData::CardType::Special_ROL:
		{
			return Operation(Operation::OperationType::ROL, 0b0001);
		}
		case CardData::CardType::Special_ROR:
		{
			return Operation(Operation::OperationType::ROR, 0b0001);
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
	return this->cardData->getAttack();
}

unsigned int Card::getAttack()
{
	unsigned int attack = this->cardData->getAttack();

	for (auto next : this->operations)
	{
		Operation operation = next;
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
	if (this->cardData->getCardKey() == CardKeys::Absorb)
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
		case Operation::OperationType::ROL:
		{
			attack = (attack << operation.immediate) | ((attack & 0b1000) >> 3);
			break;
		}
		case Operation::OperationType::ROR:
		{
			attack = (attack >> operation.immediate) | ((attack & 0b0001) << 3);
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

void Card::showUI()
{
	this->cardFront->setVisible(true);
	this->cardLabel->setVisible(true);
}

void Card::hideUI()
{
	this->cardFront->setVisible(false);
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
		EaseSineInOut::create(MoveTo::create(cardDrawDelay, Vec2(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f)))
	);

	this->runAction(
		ScaleTo::create(cardDrawDelay, 1.0f)
	);
}

void Card::updateText()
{
	unsigned int actualAttack = this->getAttack();

	switch (this->cardData->getCardType())
	{
		case CardData::CardType::Binary:
		{
			this->cardString->setString(HackUtils::toBinary4(this->getAttack()));
			this->cardLabel->setTextColor(Card::BinaryColor);
			break;
		}
		case CardData::CardType::Decimal:
		{
			this->cardString->setString(std::to_string(this->getAttack()));
			this->cardLabel->setTextColor(Card::DecimalColor);
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			this->cardString->setString(HackUtils::toHex(this->getAttack()));
			this->cardLabel->setTextColor(Card::HexColor);
			break;
		}
		default:
		{
			this->cardString->setString(this->cardData->getCardTypeString()->getString());
			this->cardLabel->setTextColor(Card::SpecialColor);
			break;
		}
	}

	if (actualAttack > this->cardData->getAttack())
	{
		this->cardLabel->setTextColor(Card::BuffColor);
	}
	else if (actualAttack < this->cardData->getAttack())
	{
		this->cardLabel->setTextColor(Card::DebuffColor);
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

void Card::runOverflowEffect(bool offsetYPosition)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	bool isHighOnScreen = GameUtils::getScreenBounds(this).getMinY() >= visibleSize.height - 256.0f;

	this->overflowLabel->setPosition(Vec2(0.0f, isHighOnScreen ? (-64.0f + (offsetYPosition ? -32.0f : 0.0f)) : (64.0f + (offsetYPosition ? 32.0f : 0.0f))));
	this->overflowLabel->setOpacity(255);
	this->overflowLabel->runAction(FadeTo::create(1.0f, 0));

	if (isHighOnScreen)
	{
		this->overflowLabel->runAction(MoveTo::create(1.0f, Vec2(0.0f, -64.0f - 96.0f - (offsetYPosition ? 32.0f : 0.0f))));
	}
	else
	{
		this->overflowLabel->runAction(MoveTo::create(1.0f, Vec2(0.0f, 64.0f + 96.0f + (offsetYPosition ? 32.0f : 0.0f))));
	}
}

void Card::runUnderflowEffect(bool offsetYPosition, bool isGoodEffect)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	bool isHighOnScreen = GameUtils::getScreenBounds(this).getMinY() >= visibleSize.height - 256.0f;\

	this->underflowLabel->setTextColor(isGoodEffect ? Color4B::GREEN : Color4B::RED);

	this->underflowLabel->setPosition(Vec2(0.0f, isHighOnScreen ? (-64.0f + (offsetYPosition ? -32.0f : 0.0f)) : (64.0f + (offsetYPosition ? 32.0f : 0.0f))));
	this->underflowLabel->setOpacity(255);
	this->underflowLabel->runAction(FadeTo::create(1.0f, 0));

	if (isHighOnScreen)
	{
		this->underflowLabel->runAction(MoveTo::create(1.0f, Vec2(0.0f, -64.0f - 96.0f - (offsetYPosition ? 32.0f : 0.0f))));
	}
	else
	{
		this->underflowLabel->runAction(MoveTo::create(1.0f, Vec2(0.0f, 64.0f + 96.0f + (offsetYPosition ? 32.0f : 0.0f))));
	}
}

CardEffects::CardEffect Card::getCorrespondingCardEffect()
{
	switch (this->cardData->getCardType())
	{
		case CardData::CardType::Special_SHL:
		{
			return CardEffects::CardEffect::MeteorPurple;
		}
		case CardData::CardType::Special_SHR:
		{
			return CardEffects::CardEffect::MeteorBlue;
		}
		case CardData::CardType::Special_ROL:
		{
			return CardEffects::CardEffect::StarBurst;
		}
		case CardData::CardType::Special_ROR:
		{
			return CardEffects::CardEffect::StarHit;
		}
		case CardData::CardType::Special_FLIP1:
		{
			return CardEffects::CardEffect::TargetPulse;
		}
		case CardData::CardType::Special_FLIP2:
		{
			return CardEffects::CardEffect::FrostCirlce;
		}
		case CardData::CardType::Special_FLIP3:
		{
			return CardEffects::CardEffect::RadialGalaxy;
		}
		case CardData::CardType::Special_FLIP4:
		{
			return CardEffects::CardEffect::RadialFire;
		}
		case CardData::CardType::Special_MOV:
		case CardData::CardType::Special_RETURN_TO_HAND:
		case CardData::CardType::Special_STEAL:
		{
			return CardEffects::CardEffect::DustPoof;
		}
		case CardData::CardType::Special_AND:
		{
			return CardEffects::CardEffect::FireBlast;
		}
		case CardData::CardType::Special_OR:
		{
			return CardEffects::CardEffect::Lightning;
		}
		case CardData::CardType::Special_XOR:
		{
			return CardEffects::CardEffect::RadialStorm;
		}
		case CardData::CardType::Special_ADD:
		{
			return CardEffects::CardEffect::MagicBurst;
		}
		case CardData::CardType::Special_SUB:
		{
			return CardEffects::CardEffect::StarHit;
		}
		case CardData::CardType::Special_NOT:
		case CardData::CardType::Special_KILL:
		{
			return CardEffects::CardEffect::Bite;
		}
		default:
		{
			// Just return an unused effect for now for debugging
			return CardEffects::CardEffect::Poison;
		}
	}
}
