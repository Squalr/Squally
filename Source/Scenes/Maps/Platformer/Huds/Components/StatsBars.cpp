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

StatsBars* StatsBars::create(bool isFrameOnLeft)
{
	StatsBars* instance = new StatsBars(isFrameOnLeft);

	instance->autorelease();

	return instance;
}

StatsBars::StatsBars(bool isFrameOnLeft)
{
	const Vec2 fillOffset = Vec2(0.0f, 0.0f);

	this->isFrameOnLeft = isFrameOnLeft;
	this->target = nullptr;
	this->frame = Sprite::create(UIResources::HUD_Frame);
	this->heartBar = CProgressBar::create(Sprite::create(UIResources::HUD_HPBarFrame), Sprite::create(UIResources::HUD_HPBarFill), fillOffset);
	this->specialBar = CProgressBar::create(Sprite::create(UIResources::HUD_MPBarFrame), Sprite::create(UIResources::HUD_MPBarFill), fillOffset);

	for (int index = 0; index < StatsBars::RuneCount; index++)
	{
		Sprite* emptyRune = Sprite::create(UIResources::HUD_TearSlot);
		Sprite* rune = Sprite::create(UIResources::HUD_Tear);

		emptyRune->setAnchorPoint(Vec2(0.0f, 0.5f));
		rune->setAnchorPoint(Vec2(0.0f, 0.5f));

		emptyRunes.push_back(emptyRune);
		filledRunes.push_back(rune);
	}

	this->frame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->heartBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->specialBar->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->frame);
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

	float barInset = this->isFrameOnLeft ? 80.0f : 0.0f;
	float runeInset = this->isFrameOnLeft ? 8.0f : 64.0f;
	float frameOffset = this->isFrameOnLeft ? 0.0f : (this->heartBar->getContentSize().width + 12.0f);

	this->frame->setPosition(Vec2(frameOffset, -this->heartBar->getContentSize().height));
	this->heartBar->setPosition(Vec2(barInset + this->heartBar->getContentSize().width / 2.0f, 0.0f));
	this->specialBar->setPosition(Vec2(barInset + this->specialBar->getContentSize().width / 2.0f, -this->heartBar->getContentSize().height));

	int index = 0;

	for (auto it = this->emptyRunes.begin(); it != this->emptyRunes.end(); it++)
	{
		(*it)->setPosition(Vec2(barInset + runeInset + (float)index * 34.0f, -this->heartBar->getContentSize().height - this->specialBar->getContentSize().height - 24.0f));

		index++;
	}

	index = 0;

	for (auto it = this->filledRunes.begin(); it != this->filledRunes.end(); it++)
	{
		(*it)->setPosition(Vec2(barInset + runeInset + (float)index * 34.0f, -this->heartBar->getContentSize().height - this->specialBar->getContentSize().height - 24.0f));

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

	this->frame->removeAllChildren();

	Sprite* emblem = Sprite::create(target->getEmblemResource());

	this->frame->addChild(emblem);

	emblem->setFlippedX(!this->isFrameOnLeft);
	emblem->setPosition(this->frame->getContentSize() / 2.0f);
}
