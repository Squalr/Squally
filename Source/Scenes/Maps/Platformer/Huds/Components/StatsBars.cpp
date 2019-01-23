#include "StatsBars.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const int StatsBars::RuneCount = 4;

StatsBars* StatsBars::create()
{
	StatsBars* instance = new StatsBars();

	instance->autorelease();

	return instance;
}

StatsBars::StatsBars()
{
	this->heart = Sprite::create(UIResources::HUD_Heart);
	this->special = Sprite::create(UIResources::HUD_Leaves);
	this->heartFrame = Sprite::create(UIResources::HUD_BarFrame);
	this->specialFrame = Sprite::create(UIResources::HUD_BarFrame);
	this->heartBar = Sprite::create(UIResources::HUD_HealthBar);
	this->specialBar = Sprite::create(UIResources::HUD_SpecialBar);

	for (int index = 0; index < StatsBars::RuneCount; index++)
	{
		Sprite* emptyRune = Sprite::create(UIResources::HUD_TearSlot);
		Sprite* rune = Sprite::create(UIResources::HUD_Tear);

		emptyRune->setAnchorPoint(Vec2(0.0f, 0.5f));
		rune->setAnchorPoint(Vec2(0.0f, 0.5f));

		emptyRunes.push_back(emptyRune);
		filledRunes.push_back(rune);
	}

	this->heart->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->special->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->heartFrame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->specialFrame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->heartBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->specialBar->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->heart);
	this->addChild(this->special);
	this->addChild(this->heartFrame);
	this->addChild(this->specialFrame);
	this->addChild(this->heartBar);
	this->addChild(this->specialBar);

	for (auto it = this->emptyRunes.begin(); it != this->emptyRunes.end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->filledRunes.begin(); it != this->filledRunes.end(); it++)
	{
		this->addChild(*it);
	}
}

void StatsBars::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void StatsBars::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float barInset = 64.0f;

	this->heart->setPosition(Vec2(0.0f, -8.0f));
	this->heartFrame->setPosition(Vec2(barInset, 12.0f));
	this->heartBar->setPosition(Vec2(barInset + 10.0f, 12.0f));
	this->special->setPosition(Vec2(barInset + 120.0f, -8.0f));
	this->specialFrame->setPosition(Vec2(barInset, 12.0f - 32.0f));
	this->specialBar->setPosition(Vec2(barInset + 10.0f, 12.0f - 32.0f));

	int index = 0;

	for (auto it = this->emptyRunes.begin(); it != this->emptyRunes.end(); it++)
	{
		(*it)->setPosition(Vec2(barInset + (float)index * 34.0f, -32.0f - 24.0f));

		index++;
	}

	index = 0;

	for (auto it = this->filledRunes.begin(); it != this->filledRunes.end(); it++)
	{
		(*it)->setPosition(Vec2(barInset + (float)index * 34.0f, -32.0f - 24.0f));

		index++;
	}
}

void StatsBars::initializeListeners()
{
	super::initializeListeners();
}

void StatsBars::update(float dt)
{
	super::update(dt);
}
