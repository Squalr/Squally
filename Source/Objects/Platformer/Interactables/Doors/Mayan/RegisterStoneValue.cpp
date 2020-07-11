#include "RegisterStoneValue.h"

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

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string RegisterStoneValue::MapKey = "register-stone-value";
const std::string RegisterStoneValue::PropertyRegister = "register";
const std::string RegisterStoneValue::PropertyValue = "value";

RegisterStoneValue* RegisterStoneValue::create(ValueMap& properties)
{
	RegisterStoneValue* instance = new RegisterStoneValue(properties);

	instance->autorelease();

	return instance;
}

RegisterStoneValue::RegisterStoneValue(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, Size(100.0f, 118.0f))
{
	std::string valueStr = GameUtils::getKeyOrDefault(this->properties, RegisterStoneValue::PropertyValue, Value("0")).asString();
	
	this->registerStr = GameUtils::getKeyOrDefault(this->properties, RegisterStoneValue::PropertyRegister, Value("")).asString();
	this->value = 0;
	this->registerStone = Sprite::create(ObjectResources::Puzzles_Stack_RegisterBlock);
	this->valueStone = Sprite::create(ObjectResources::Puzzles_Stack_StackBlock);
	this->valueString = ConstantString::create(std::to_string(this->value));
	this->valueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->valueString);
	this->registerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->buildRegisterString());

	this->addTag(this->registerStr);
	this->valueLabel->enableOutline(Color4B::BLACK, 2);
	this->registerLabel->enableOutline(Color4B::BLACK, 2);
	this->setValue(StrUtils::isInteger(valueStr) ? std::stoi(valueStr) : 0);
	
	this->addChild(this->registerStone);
	this->addChild(this->valueStone);
	this->addChild(this->valueLabel);
	this->addChild(this->registerLabel);
}

RegisterStoneValue::~RegisterStoneValue()
{
}

void RegisterStoneValue::onEnter()
{
	super::onEnter();
}

void RegisterStoneValue::initializePositions()
{
	super::initializePositions();

	const float BaseY = -registerStone->getContentSize().height / 2.0f;

	this->registerStone->setPositionY(BaseY);
	this->registerLabel->setPositionY(BaseY - 4.0f);
	this->valueStone->setPositionY(BaseY + 42.0f);
	this->valueLabel->setPositionY(BaseY + 42.0f - 4.0f);
}

void RegisterStoneValue::initializeListeners()
{
	super::initializeListeners();
}

void RegisterStoneValue::setValue(int value)
{
	this->value = value;

	this->valueString->setString(std::to_string(this->value));
}

ConstantString* RegisterStoneValue::buildRegisterString()
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
