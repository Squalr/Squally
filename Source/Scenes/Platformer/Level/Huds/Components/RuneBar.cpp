#include "RuneBar.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/XOverY.h"

using namespace cocos2d;

RuneBar* RuneBar::create(bool isFrameOnLeft)
{
	RuneBar* instance = new RuneBar(isFrameOnLeft);

	instance->autorelease();

	return instance;
}

RuneBar::RuneBar(bool isFrameOnLeft)
{
	this->target = nullptr;

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		Sprite* emptyRune = Sprite::create(UIResources::HUD_EyeSlot);
		Sprite* rune = Sprite::create(UIResources::HUD_Eye);

		emptyRune->setAnchorPoint(Vec2(0.0f, 0.5f));
		rune->setAnchorPoint(Vec2(0.0f, 0.5f));

		emptyRunes.push_back(emptyRune);
		filledRunes.push_back(rune);
	}

	for (auto it = this->emptyRunes.begin(); it != this->emptyRunes.end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->filledRunes.begin(); it != this->filledRunes.end(); it++)
	{
		this->addChild(*it);
	}
}

RuneBar::~RuneBar()
{
}

void RuneBar::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void RuneBar::initializePositions()
{
	super::initializePositions();

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		this->emptyRunes[index]->setPosition(Vec2(0.0f, (float)index * -34.0f));
		this->filledRunes[index]->setPosition(Vec2(0.0f, (float)index * -34.0f));
	}
}

void RuneBar::initializeListeners()
{
	super::initializeListeners();
}

void RuneBar::update(float dt)
{
	super::update(dt);

	if (this->target == nullptr)
	{
		return;
	}

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

void RuneBar::setStatsTarget(PlatformerEntity* target)
{
	this->target = target;

	if (this->target == nullptr)
	{
		for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
		{
			this->filledRunes[index]->setVisible(true);
			this->emptyRunes[index]->setVisible(false);
		}
	}
}
