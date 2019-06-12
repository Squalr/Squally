#include "IqEqDisplay.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const int IqEqDisplay::IqCacheCipher = 0x48195623;
const int IqEqDisplay::EqCacheCipher = 0x68203174;

IqEqDisplay* IqEqDisplay::create()
{
	IqEqDisplay* instance = new IqEqDisplay();

	instance->autorelease();

	return instance;
}

IqEqDisplay::IqEqDisplay()
{
	this->iqFrame = Sprite::create(UIResources::HUD_EmblemGlow);
	this->eqFrame = Sprite::create(UIResources::HUD_EmblemGlow);
	this->iqValue = ConstantString::create("0");
	this->eqValue = ConstantString::create("0");
	this->iqLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->eqValue);
	this->eqLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->iqValue);

	this->eqLabel->enableOutline(Color4B::BLACK, 2);
	this->iqLabel->enableOutline(Color4B::BLACK, 2);

	this->cachedIq = (0 ^ IqEqDisplay::IqCacheCipher);
	this->cachedEq = (0 ^ IqEqDisplay::EqCacheCipher);

	this->addChild(this->iqFrame);
	this->addChild(this->eqFrame);
	this->addChild(this->iqLabel);
	this->addChild(this->eqLabel);
}

IqEqDisplay::~IqEqDisplay()
{
}

void IqEqDisplay::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void IqEqDisplay::initializePositions()
{
	super::initializePositions();

	this->iqFrame->setPosition(Vec2(-24.0f, 0.0f));
	this->iqLabel->setPosition(Vec2(-24.0f, 0.0f));
	this->eqFrame->setPosition(Vec2(24.0f, 0.0f));
	this->eqLabel->setPosition(Vec2(24.0f, 0.0f));
}

void IqEqDisplay::initializeListeners()
{
	super::initializeListeners();
}

void IqEqDisplay::update(float dt)
{
	super::update(dt);

	if (this->target == nullptr)
	{
		return;
	}

	int eq = this->target->getEq();

	if (eq != (this->cachedEq ^ IqEqDisplay::EqCacheCipher))
	{
		this->cachedEq = (eq ^ IqEqDisplay::EqCacheCipher);

		this->eqValue->setString(std::to_string(eq));
	}

	int iq = this->target->getIq();

	if (iq != (this->cachedIq ^ IqEqDisplay::IqCacheCipher))
	{
		this->cachedIq = (iq ^ IqEqDisplay::IqCacheCipher);

		this->iqValue->setString(std::to_string(iq));
	}
}

void IqEqDisplay::setStatsTarget(Squally* target)
{
	this->eqValue->setString("0");
	this->iqValue->setString("0");
	this->cachedEq = (0 ^ IqEqDisplay::EqCacheCipher);
	this->cachedIq = (0 ^ IqEqDisplay::IqCacheCipher);
	
	this->target = target;
}
