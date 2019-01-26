#include "StatsBars.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/UI/Controls/CProgressBar.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"
#include "Engine/Utils/MathUtils.h"

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
	const Vec2 fillOffset = Vec2(0.0f, 0.0f);

	this->target = nullptr;
	this->heart = Sprite::create(UIResources::HUD_Heart);
	this->special = Sprite::create(UIResources::HUD_Leaves);
	this->heartBar = CProgressBar::create(Sprite::create(UIResources::HUD_BarFrame), Sprite::create(UIResources::HUD_HealthBar), fillOffset);
	this->specialBar = CProgressBar::create(Sprite::create(UIResources::HUD_BarFrame), Sprite::create(UIResources::HUD_SpecialBar), fillOffset);

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
	this->heartBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->specialBar->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->heart);
	this->addChild(this->special);
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

	this->heart->setPosition(Vec2(0.0f, -32.0f));
	this->heartBar->setPosition(Vec2(barInset + this->heartBar->getContentSize().width / 2.0f, 0.0f));
	this->special->setPosition(Vec2(barInset + 120.0f, -32.0f));
	this->specialBar->setPosition(Vec2(barInset + this->specialBar->getContentSize().width / 2.0f, -32.0f));

	int index = 0;

	for (auto it = this->emptyRunes.begin(); it != this->emptyRunes.end(); it++)
	{
		(*it)->setPosition(Vec2(barInset + (float)index * 34.0f, -64.0f - 24.0f));

		index++;
	}

	index = 0;

	for (auto it = this->filledRunes.begin(); it != this->filledRunes.end(); it++)
	{
		(*it)->setPosition(Vec2(barInset + (float)index * 34.0f, -64.0f - 24.0f));

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

	if (this->target == nullptr)
	{
		return;
	}

	int health = this->target->getHealth();
	int maxHealth = this->target->getMaxHealth();
	float healthPercent = MathUtils::clamp((float)health / (maxHealth == 0 ? 1.0f : (float)maxHealth), 0.0f, 1.0f);

	this->heartBar->setProgress(healthPercent);

	int special = this->target->getSpecial();
	int maxSpecial = this->target->getMaxSpecial();
	float specialPercent = MathUtils::clamp((float)special / (maxSpecial == 0 ? 1.0f : (float)maxSpecial), 0.0f, 1.0f);

	this->specialBar->setProgress(specialPercent);

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		if (index < this->target->getRunes())
		{
			this->filledRunes[index]->setVisible(true);
			this->emptyRunes[index]->setVisible(false);
		}
		else
		{
			this->filledRunes[index]->setVisible(false);
			this->emptyRunes[index]->setVisible(true);
		}
	}
}

void StatsBars::setStatsTarget(PlatformerEntity* target)
{
	this->target = target;
}
