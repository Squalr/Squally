#include "Monkey.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"

#include "Resources/ObjectResources.h"

#include "Strings/Common/Constant.h"
#include "Strings/Common/Empty.h"
#include "Strings/Common/PlusConstant.h"

using namespace cocos2d;

const std::string Monkey::MapKeyMonkey = "animal-monkey";
int Monkey::lockCountDown = 234900;

Monkey* Monkey::create(ValueMap& initProperties)
{
	Monkey* instance = new Monkey(initProperties);

	instance->autorelease();

	return instance;
}

Monkey::Monkey(ValueMap& initProperties) : super(initProperties)
{
	this->spriteNode->addChild(Sprite::create(ObjectResources::Collectables_Animals_MONKEY));

	this->valueString = ConstantString::create();
	this->valueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Common_Constant::create());

	this->valueString->setString(std::to_string(Monkey::lockCountDown));

	this->valueLabel->setStringReplacementVariables(this->valueString);
	this->valueLabel->setPosition(-48.0f, 128.0f);
	this->valueLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->valueLabel);
}

Monkey::~Monkey()
{
}

void Monkey::onEnter()
{
	super::onEnter();

	CallFunc* decCountdown = CallFunc::create([=]
	{
		this->decreaseLockTimer();
	});

	decCountdown->retain();

	this->runAction(RepeatForever::create(
		Sequence::create(
			decCountdown,
			DelayTime::create(1.0f),
			nullptr)
		)
	);

	this->scheduleUpdate();
}

void Monkey::update(float dt)
{
	super::update(dt);

	// Update text if values have changed
	if (~previousValue != Monkey::lockCountDown)
	{
		// Constrain value
		Monkey::lockCountDown = std::max(0, Monkey::lockCountDown);

		// Update text
		this->valueString->setString(std::to_string(Monkey::lockCountDown));

		// Set color
		if (Monkey::lockCountDown > 0)
		{
			this->valueLabel->setColor(Color3B::RED);
		}
		else
		{
			this->valueLabel->setColor(Color3B::GREEN);
		}

		// Store the previous value as a bit inverse (so that the previous values do not show up in scan results)
		previousValue = ~Monkey::lockCountDown;
	}
}

void Monkey::decreaseLockTimer()
{
	/*
	ASM(push ZCX);
	ASM(mov ZCX, lockCountDown);

	HACKABLE_CODE_BEGIN(assemblyAddressStart);
	ASM(dec ZCX);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	HACKABLE_CODE_END(assemblyAddressEnd);

	ASM(mov lockCountDown, ZCX);
	ASM(pop ZCX);

	if (Monkey::lockCountDown < 0)
	{
		Monkey::lockCountDown = 0;
	}
	*/
}

void Monkey::registerHackables()
{
	super::registerHackables();
}
