#include "TimeBombTickPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

TimeBombTickPreview* TimeBombTickPreview::create()
{
	TimeBombTickPreview* instance = new TimeBombTickPreview();

	instance->autorelease();

	return instance;
}

TimeBombTickPreview::TimeBombTickPreview()
{
	this->timeBomb = Sprite::create(ObjectResources::Traps_TimeBomb_BOMB);

	this->tick = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("7"));

	this->timeBomb->setScale(0.35f);

	this->previewNode->addChild(this->timeBomb);
	this->assemblyTextNode->addChild(this->tick);
}

TimeBombTickPreview::~TimeBombTickPreview()
{
}

HackablePreview* TimeBombTickPreview::clone()
{
	return TimeBombTickPreview::create();
}

void TimeBombTickPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;

	this->timeBomb->setPosition(Vec2(0.0f, 16.0f));
}

void TimeBombTickPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 32.0f;
	
	this->tick->setPosition(Vec2(-HackablePreview::PreviewRadius + offset, -16.0f));
}
