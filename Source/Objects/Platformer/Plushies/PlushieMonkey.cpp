#include "PlushieMonkey.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"

#include "Resources/UIResources.h"

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
	Label* gold = Label::createWithTTF("+200", Localization::getMainFont(), 24.0f);
	gold->enableOutline(Color4B::BLACK, 2);

	coin->setScale(0.5f);
	coin->setPosition(Vec2(-48.0f, 0.0f));

	//this->sprite->addChild(Sprite::create(Resources::Plushies_MONKEY));
	this->sprite->addChild(coin);
	this->sprite->addChild(gold);

	this->valueLabel = Label::createWithTTF(std::to_string(PlushieMonkey::lockCountDown), Localization::getMainFont(), 24.0f);

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
		this->valueLabel->setString(std::to_string(PlushieMonkey::lockCountDown));

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
	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	ASM(push ecx);
	ASM(mov ecx, PlushieMonkey::lockCountDown);

	HACKABLE_CODE_BEGIN(assemblyAddressStart, puzzleStart);
	ASM(dec ecx);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	HACKABLE_CODE_END(assemblyAddressEnd, puzzleEnd);

	ASM(mov PlushieMonkey::lockCountDown, ecx);
	ASM(pop ecx);

	if (PlushieMonkey::lockCountDown < 0)
	{
		PlushieMonkey::lockCountDown = 0;
	}

	this->puzzleData->registerCode(assemblyAddressStart, assemblyAddressEnd, "Lock Countdown", UIResources::Menus_Icons_Safe);
	this->puzzleData->registerCode((void*)((unsigned int)((unsigned long)assemblyAddressStart + 1)), assemblyAddressEnd, "Puzzle Test", UIResources::Menus_Icons_FlamingScroll);
	this->puzzleData->registerCode((void*)((unsigned int)((unsigned long)assemblyAddressStart + 2)), assemblyAddressEnd, "Puzzle Swag", UIResources::Menus_Icons_BookCrystal);
}

void PlushieMonkey::registerHackables()
{
	Plushie::registerHackables();

	this->puzzleData = HackableData::create("Key", &PlushieMonkey::lockCountDown, &typeid(PlushieMonkey::lockCountDown), UIResources::Menus_Icons_Lock);
	this->registerData(this->puzzleData);
	
	this->registerData(HackableData::create("Health", this->chest, &typeid((unsigned int)((unsigned long)this->chest)), UIResources::Menus_Icons_Heart));
	//this->registerCode(HackableCode::create("Test", this->chest, 10, Resources::Menus_HackerModeMenu_Icons_AlchemyPot));
}
