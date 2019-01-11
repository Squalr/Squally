#include "PlushieMonkey.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Objects/Platformer/Chest.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Constant.h"
#include "Strings/Generics/Empty.h"
#include "Strings/Generics/PlusConstant.h"

using namespace cocos2d;

const std::string PlushieMonkey::MapKeyPlushieMonkey = "plushie_monkey";
int PlushieMonkey::lockCountDown = 234900;

PlushieMonkey* PlushieMonkey::create(ValueMap* initProperties)
{
	PlushieMonkey* instance = new PlushieMonkey(initProperties);

	instance->autorelease();

	return instance;
}

PlushieMonkey::PlushieMonkey(ValueMap* initProperties) : Plushie(initProperties)
{
	Sprite* coin = Sprite::create(UIResources::Menus_Icons_Coins);

	ConstantString* goldString = ConstantString::create("+200");
	LocalizedLabel* gold = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Generics_PlusConstant::create());

	gold->setStringReplacementVariables(goldString);
	gold->enableOutline(Color4B::BLACK, 2);

	coin->setScale(0.5f);
	coin->setPosition(Vec2(-48.0f, 0.0f));

	//this->sprite->addChild(Sprite::create(Resources::Plushies_MONKEY));
	this->sprite->addChild(coin);
	this->sprite->addChild(gold);

	this->valueString = ConstantString::create();
	this->valueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Generics_Constant::create());

	this->valueString->setString(std::to_string(PlushieMonkey::lockCountDown));

	this->valueLabel->setStringReplacementVariables(this->valueString);
	this->valueLabel->setPosition(-48.0f, 128.0f);
	this->valueLabel->enableOutline(Color4B::BLACK, 2.0f);

	this->registerHackables();

	this->addChild(this->valueLabel);
}

PlushieMonkey::~PlushieMonkey()
{
}

void PlushieMonkey::onEnter()
{
	Plushie::onEnter();

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

void PlushieMonkey::update(float dt)
{
	Plushie::update(dt);

	// Update text if values have changed
	if (~previousValue != PlushieMonkey::lockCountDown)
	{
		// Constrain value
		PlushieMonkey::lockCountDown = std::max(0, PlushieMonkey::lockCountDown);

		// Update text
		this->valueString->setString(std::to_string(PlushieMonkey::lockCountDown));

		// Set color
		if (PlushieMonkey::lockCountDown > 0)
		{
			this->valueLabel->setColor(Color3B::RED);
			this->chest->close();
		}
		else
		{
			this->valueLabel->setColor(Color3B::GREEN);
			this->chest->open();
		}

		// Store the previous value as a bit inverse (so that the previous values do not show up in scan results)
		previousValue = ~PlushieMonkey::lockCountDown;
	}
}

void PlushieMonkey::decreaseLockTimer()
{
	/*
	ASM(push ECX);
	ASM(mov ECX, lockCountDown);

	HACKABLE_CODE_BEGIN(assemblyAddressStart);
	ASM(dec ecx);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	HACKABLE_CODE_END(assemblyAddressEnd);

	ASM(mov lockCountDown, ECX);
	ASM(pop ECX);

	if (PlushieMonkey::lockCountDown < 0)
	{
		PlushieMonkey::lockCountDown = 0;
	}
	*/
}

void PlushieMonkey::registerHackables()
{
	Plushie::registerHackables();

	this->puzzleData = HackableData::create(
		&PlushieMonkey::lockCountDown,
		Strings::Generics_Empty::create(),
		typeid(PlushieMonkey::lockCountDown),
		UIResources::Menus_Icons_Lock,
		nullptr
	);
	this->registerData(this->puzzleData);
	
	this->registerData(HackableData::create(
		this->chest,
		Strings::Generics_Empty::create(),
		typeid((unsigned int)((unsigned long)this->chest)),
		UIResources::Menus_Icons_Heart,
		nullptr
	));
	//this->registerCode(HackableCode::create("Test", this->chest, 10, Resources::Menus_HackerModeMenu_Icons_AlchemyPot));
}
