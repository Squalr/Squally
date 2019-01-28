#include "TimelineEntry.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/UI/Controls/CProgressBar.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const float TimelineEntry::CastPercentage = 0.8f;

TimelineEntry* TimelineEntry::create(PlatformerEntity* entity, bool isPlayerEntry, std::function<void(TimelineEntry*)> onCastingStartCallback)
{
	TimelineEntry* instance = new TimelineEntry(entity, isPlayerEntry, onCastingStartCallback);

	instance->autorelease();

	return instance;
}

TimelineEntry::TimelineEntry(PlatformerEntity* entity, bool isPlayerEntry, std::function<void(TimelineEntry*)> onCastingStartCallback)
{
	this->line = Sprite::create(UIResources::Combat_Line);
	this->circle = isPlayerEntry ? Sprite::create(UIResources::Combat_PlayerCircle) : Sprite::create(UIResources::Combat_EnemyCircle);
	this->emblem = Sprite::create();

	this->onCastingStartCallback = onCastingStartCallback;
	this->isPlayerEntry = isPlayerEntry;

	this->speed = 1.0f;
	this->progress = 0.0f;

	this->addChild(this->line);
	this->addChild(this->circle);
}

void TimelineEntry::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void TimelineEntry::initializePositions()
{
	super::initializePositions();

	const float EntryOffsetY = 72.0f;

	if (this->isPlayerEntry)
	{
		this->line->setAnchorPoint(Vec2(0.5f, 0.0f));
		this->line->setPositionY(-(EntryOffsetY - 8.0f));
		this->setPositionY(EntryOffsetY);
	}
	else
	{
		this->line->setAnchorPoint(Vec2(0.5f, 1.0f));
		this->line->setPositionY(EntryOffsetY - 8.0f);
		this->setPositionY(-EntryOffsetY);
	}
}

void TimelineEntry::initializeListeners()
{
	super::initializeListeners();
}

void TimelineEntry::update(float dt)
{
	super::update(dt);
}

bool TimelineEntry::isPlayerTimelineEntry()
{
	return this->isPlayerEntry;
}

bool TimelineEntry::isCasting()
{
	return this->progress > TimelineEntry::CastPercentage;
}

void TimelineEntry::doCast()
{
	// TODO
}

void TimelineEntry::interrupt()
{
	if (this->isCasting())
	{
		// Interrupt
	}
	else
	{
		// Knockback
	}
}

float TimelineEntry::getProgress()
{
	return this->progress;
}

float TimelineEntry::cancelProgress()
{
	this->progress = 0.0f;

	return this->progress;
}

float TimelineEntry::addProgress(float progressDelta)
{
	bool wasCasting = this->isCasting();

	this->progress += progressDelta;

	// Progress complete, do the cast
	if (this->progress > 1.0f)
	{
		this->progress = std::fmod(this->progress, 1.0f);
		this->doCast();
	}
	// Cast started
	else if (!wasCasting && this->isCasting() && this->onCastingStartCallback != nullptr)
	{
		this->onCastingStartCallback(this);
	}

	return this->progress;
}

float TimelineEntry::getSpeed()
{
	return this->speed;
}
