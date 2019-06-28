#include "EqDisplay.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/XOverY.h"

using namespace cocos2d;

const int EqDisplay::EqCacheCipher = 0x68203174;

EqDisplay* EqDisplay::create()
{
	EqDisplay* instance = new EqDisplay();

	instance->autorelease();

	return instance;
}

EqDisplay::EqDisplay()
{
	this->eqFrame = Sprite::create(UIResources::HUD_LevelFrame);
	this->eqValue = ConstantString::create("0");
	this->eqLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->eqValue);

	this->eqLabel->enableOutline(Color4B::BLACK, 2);

	this->cachedEq = (0 ^ EqDisplay::EqCacheCipher);

	this->addChild(this->eqFrame);
	this->addChild(this->eqLabel);
}

EqDisplay::~EqDisplay()
{
}

void EqDisplay::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void EqDisplay::initializePositions()
{
	super::initializePositions();

	this->eqFrame->setPosition(Vec2(0.0f, 4.0f));
	this->eqLabel->setPosition(Vec2(0.0f, 0.0f));
}

void EqDisplay::initializeListeners()
{
	super::initializeListeners();
}

void EqDisplay::update(float dt)
{
	super::update(dt);

	if (this->target == nullptr)
	{
		return;
	}

	int eq = this->target->getEq();

	if (eq != (this->cachedEq ^ EqDisplay::EqCacheCipher))
	{
		this->cachedEq = (eq ^ EqDisplay::EqCacheCipher);

		this->eqValue->setString(std::to_string(eq));
	}
}

void EqDisplay::setStatsTarget(Squally* target)
{
	this->eqValue->setString("0");
	this->cachedEq = (0 ^ EqDisplay::EqCacheCipher);
	
	this->target = target;

	if (this->target == nullptr)
	{
		this->setVisible(false);
	}
	else
	{
		this->setVisible(true);
	}
}
