#include "RegisterStone.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanDoor.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RegisterStone::MapKey = "register-stone";
const std::string RegisterStone::PropertyRegister = "register";
const std::string RegisterStone::PropertyValue = "value";
const std::string RegisterStone::PropertyCorrectValue = "correct-value";

RegisterStone* RegisterStone::create(ValueMap& properties)
{
	RegisterStone* instance = new RegisterStone(properties);

	instance->autorelease();

	return instance;
}

RegisterStone::RegisterStone(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, Size(100.0f, 118.0f), Vec2::ZERO, Strings::Platformer_Objects_Interaction_OperationPop::create(), EventKeyboard::KeyCode::KEY_V, Color3B(16, 23, 57))
{
	std::string valueStr = GameUtils::getKeyOrDefault(this->properties, RegisterStone::PropertyValue, Value("0")).asString();
	std::string correctValueStr = GameUtils::getKeyOrDefault(this->properties, RegisterStone::PropertyCorrectValue, Value("0")).asString();

	this->registerStr = GameUtils::getKeyOrDefault(this->properties, RegisterStone::PropertyRegister, Value("")).asString();
	this->value = StrUtils::isInteger(valueStr) ? std::stoi(valueStr) : 0;
	this->originalValue = this->value;
	this->correctValue = StrUtils::isInteger(correctValueStr) ? std::stoi(correctValueStr) : 0;
	this->registerStone = Sprite::create(ObjectResources::Puzzles_Stack_RegisterBlock);
	this->valueStone = Sprite::create(ObjectResources::Puzzles_Stack_StackBlock);
	this->valueString = ConstantString::create(std::to_string(this->value));
	this->valueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->valueString);
	this->animatedStone = Sprite::create(ObjectResources::Puzzles_Stack_StackBlock);
	this->animatedString = ConstantString::create(std::to_string(this->value));
	this->animatedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->animatedString);
	this->correctValueString = ConstantString::create(correctValueStr);
	this->correctValueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->correctValueString);
	this->registerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->buildRegisterString());
	this->pushInteract = InteractObject::create(InteractObject::InteractType::Input, Size(100.0f, 118.0f), Vec2::ZERO, Strings::Platformer_Objects_Interaction_OperationPush::create(), EventKeyboard::KeyCode::KEY_C, Color3B(16, 23, 57));
	this->fxGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->fxGlowTop = Sprite::create(UIResources::HUD_EmblemGlow);

	this->addTag(this->registerStr);
	this->valueLabel->enableOutline(Color4B::BLACK, 2);
	this->animatedLabel->enableOutline(Color4B::BLACK, 2);
	this->correctValueLabel->enableOutline(Color4B::BLACK, 2);
	this->registerLabel->enableOutline(Color4B::BLACK, 2);
	this->setValue(this->value);
	this->fxGlow->setOpacity(0);
	this->fxGlowTop->setOpacity(0);
	
	this->addChild(this->pushInteract);
	this->addChild(this->registerStone);
	this->addChild(this->fxGlow);
	this->addChild(this->correctValueLabel);
	this->addChild(this->valueStone);
	this->addChild(this->valueLabel);
	this->addChild(this->animatedStone);
	this->addChild(this->animatedLabel);
	this->addChild(this->fxGlowTop);
	this->addChild(this->registerLabel);
}

RegisterStone::~RegisterStone()
{
}

void RegisterStone::onEnter()
{
	super::onEnter();
}

void RegisterStone::initializePositions()
{
	super::initializePositions();

	const float Width = this->valueStone->getContentSize().width;
	const float BaseY = -this->valueStone->getContentSize().height / 2.0f;

	this->pushInteract->setPositionY(118.0f / 2.0f);
	this->registerStone->setPosition(Vec2(0.0f, BaseY));
	this->registerLabel->setPosition(Vec2(-Width / 2.0f, BaseY - 6.0f));
	this->correctValueLabel->setPosition(Vec2(Width / 2.0f, BaseY - 6.0f));
	this->fxGlow->setPosition(Vec2(Width / 2.0f, BaseY - 6.0f));
	this->valueStone->setPosition(Vec2(0.0f, BaseY + 42.0f));
	this->valueLabel->setPosition(Vec2(0.0f, BaseY + 42.0f - 6.0f));
	this->animatedStone->setPosition(valueStone->getPosition());
	this->animatedLabel->setPosition(valueLabel->getPosition());
	this->fxGlowTop->setPosition(Vec2(0.0f, BaseY + 42.0f - 6.0f));
}

void RegisterStone::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(MayanDoor::MapEventLockInteraction, [=](ValueMap args)
	{
		this->disable();
		this->pushInteract->disable();
	});

	this->listenForMapEvent(MayanDoor::MapEventUnlockInteraction, [=](ValueMap args)
	{
		this->enable();
		this->pushInteract->enable();
	});

	this->listenForMapEvent(MayanDoor::MapEventPopRet + this->registerStr, [=](ValueMap args)
	{
		this->runAnimationIn(GameUtils::getKeyOrDefault(args, MayanDoor::PropertyValue, Value(0)).asInt());
	});

	this->pushInteract->setInteractCallback([=]()
	{
		this->runAnimationOut();

		return true;
	});
}

void RegisterStone::runAnimationIn(int newValue)
{
	const float Speed = 0.5f;
	const Vec2 Delta = Vec2(0.0f, 1024.0f);

	this->broadcastMapEvent(MayanDoor::MapEventLockInteraction, ValueMap());
	this->animatedLabel->setPosition(this->valueLabel->getPosition() + Delta);
	this->animatedStone->setPosition(this->valueStone->getPosition() + Delta);

	this->animatedLabel->runAction(Sequence::create(
		MoveTo::create(Speed, this->valueLabel->getPosition()),
		nullptr
	));
	this->animatedStone->runAction(Sequence::create(
		MoveTo::create(Speed, this->valueStone->getPosition()),
		CallFunc::create([=]()
		{
			this->setValue(newValue);
			this->broadcastMapEvent(MayanDoor::MapEventUnlockInteraction, ValueMap());
		}),
		nullptr
	));
}

void RegisterStone::runAnimationOut()
{
	const float Speed = 0.5f;
	const Vec2 Delta = Vec2(0.0f, 1024.0f);
	
	this->broadcastMapEvent(MayanDoor::MapEventLockInteraction, ValueMap());

	this->animatedLabel->runAction(Sequence::create(
		MoveBy::create(Speed, Delta),
		CallFunc::create([=]()
		{
			this->animatedLabel->setPosition(this->valueLabel->getPosition());
		}),
		nullptr
	));
	this->animatedStone->runAction(Sequence::create(
		MoveBy::create(Speed, Delta),
		CallFunc::create([=]()
		{
			this->animatedStone->setPosition(this->valueStone->getPosition());

			this->broadcastMapEvent(MayanDoor::MapEventUnlockInteraction, ValueMap());

			ValueMap args = ValueMap();

			args[MayanDoor::PropertyRegister] = Value(this->registerStr);
			args[MayanDoor::PropertyValue] = Value(this->value);

			this->broadcastMapEvent(MayanDoor::MapEventPush, args);
		}),
		nullptr
	));
}

void RegisterStone::onInteract(PlatformerEntity* interactingEntity)
{
	ValueMap args = ValueMap();

	args[MayanDoor::PropertyRegister] = Value(this->registerStr);

	this->broadcastMapEvent(MayanDoor::MapEventPop, args);
}

void RegisterStone::runFx()
{
	this->fxGlow->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		DelayTime::create(0.25f),
		FadeTo::create(0.5f, 0),
		nullptr
	));

	this->fxGlowTop->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		DelayTime::create(0.25f),
		FadeTo::create(0.5f, 0),
		nullptr
	));
}

int RegisterStone::getValue()
{
	return this->value;
}

int RegisterStone::getCorrectValue()
{
	return this->correctValue;
}

void RegisterStone::setValue(int value)
{
	this->value = value;

	this->animatedString->setString(std::to_string(this->value));
	this->valueString->setString(std::to_string(this->value));
}

ConstantString* RegisterStone::buildRegisterString()
{
	ConstantString* str = ConstantString::create();

	if (sizeof(int) == 4)
	{
		str->setString(this->registerStr);
	}
	else
	{
		str->setString(StrUtils::replaceAll(this->registerStr, "e", "r"));
	}

	return str;
}
