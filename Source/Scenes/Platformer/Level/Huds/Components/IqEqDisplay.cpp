#include "IqEqDisplay.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/XOverY.h"

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
	this->iqEqFrame = Sprite::create(UIResources::HUD_LevelFrame);
	this->iqValue = ConstantString::create("0");
	this->eqValue = ConstantString::create("0");
	this->iqEqValue = Strings::Generics_XOverY::create();
	this->iqEqLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->iqEqValue);

	this->iqEqValue->setStringReplacementVariables( { this->iqValue, this->eqValue } );

	this->iqEqLabel->enableOutline(Color4B::BLACK, 2);

	this->iqEqFrame->setVisible(false);

	this->cachedIq = (0 ^ IqEqDisplay::IqCacheCipher);
	this->cachedEq = (0 ^ IqEqDisplay::EqCacheCipher);

	this->addChild(this->iqEqFrame);
	this->addChild(this->iqEqLabel);
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

	this->iqEqFrame->setPosition(Vec2(0.0f, 0.0f));
	this->iqEqLabel->setPosition(Vec2(0.0f, 0.0f));
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
