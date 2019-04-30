#include "PointerTraceHud.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Platformer/Level/Huds/Components/CurrencyDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/RuneBar.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"

using namespace cocos2d;

PointerTraceHud* PointerTraceHud::create()
{
	PointerTraceHud* instance = new PointerTraceHud();

	instance->autorelease();

	return instance;
}

PointerTraceHud::PointerTraceHud()
{
	this->eaxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->ebxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->ecxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->edxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->ediLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->esiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->ebpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->espLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));
	this->eipLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create(""));

	this->addChild(this->eaxLabel);
	this->addChild(this->ebxLabel);
	this->addChild(this->ecxLabel);
	this->addChild(this->edxLabel);
	this->addChild(this->ediLabel);
	this->addChild(this->esiLabel);
	this->addChild(this->ebpLabel);
	this->addChild(this->espLabel);
	this->addChild(this->eipLabel);
}

PointerTraceHud::~PointerTraceHud()
{
}

void PointerTraceHud::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void PointerTraceHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->eaxLabel->setPosition(24.0f, visibleSize.height - 64.0f * 0.0f - 24.0f);
	this->ebxLabel->setPosition(24.0f, visibleSize.height - 64.0f * 1.0f - 24.0f);
	this->ecxLabel->setPosition(24.0f, visibleSize.height - 64.0f * 2.0f - 24.0f);
	this->edxLabel->setPosition(24.0f, visibleSize.height - 64.0f * 3.0f - 24.0f);
	this->ediLabel->setPosition(24.0f, visibleSize.height - 64.0f * 4.0f - 24.0f);
	this->esiLabel->setPosition(24.0f, visibleSize.height - 64.0f * 5.0f - 24.0f);
	this->ebpLabel->setPosition(24.0f, visibleSize.height - 64.0f * 6.0f - 24.0f);
	this->espLabel->setPosition(24.0f, visibleSize.height - 64.0f * 7.0f - 24.0f);
	this->eipLabel->setPosition(24.0f, visibleSize.height - 64.0f * 8.0f - 24.0f);
}

void PointerTraceHud::initializeListeners()
{
	super::initializeListeners();
}

void PointerTraceHud::update(float dt)
{
	super::update(dt);
}
