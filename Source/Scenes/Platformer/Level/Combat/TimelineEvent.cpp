#include "TimelineEvent.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

TimelineEvent* TimelineEvent::create(PlatformerEntity* owner, Sprite* emblem, float offsetTime, std::function<void()> timelineEvent)
{
	TimelineEvent* instance = new TimelineEvent(owner, emblem, offsetTime, timelineEvent);

	instance->autorelease();

	return instance;
}

TimelineEvent::TimelineEvent(PlatformerEntity* owner, Sprite* emblem, float offsetTime, std::function<void()> timelineEvent)
{
	this->owner = owner;
	this->line = Sprite::create(UIResources::Combat_Line);
	this->circle = Sprite::create(UIResources::Combat_EventCircle);
	this->emblem = emblem;
	this->time = offsetTime;
	this->timelineEvent = timelineEvent;
	this->isDeactivated = false;

	this->addChild(this->line);
	this->addChild(this->circle);

	if (this->emblem != nullptr)
	{
		this->addChild(this->emblem);
	}
}

TimelineEvent::~TimelineEvent()
{
}

void TimelineEvent::initializePositions()
{
	super::initializePositions();

	const float EntryOffsetY = 72.0f;
	const float LineOffsetY = 48.0f;

	if (this->isPlayerEntry())
	{
		this->line->setPositionY(-LineOffsetY);
		this->setPositionY(EntryOffsetY);
	}
	else
	{
		this->line->setPositionY(LineOffsetY);
		this->setPositionY(-EntryOffsetY);
	}
}

void TimelineEvent::deactivate()
{
	this->setVisible(false);
	this->isDeactivated = true;
}

void TimelineEvent::setPositions(float timelineWidth)
{
	this->setPositionX(-timelineWidth / 2.0f + timelineWidth * this->getTime());
}

PlatformerEntity* TimelineEvent::getOwner()
{
	return this->owner;
}

void TimelineEvent::offsetByTimelineTime(float initialTime)
{
	this->setTime(MathUtils::wrappingNormalize(this->getTime() * TimelineEntry::BaseSpeedMultiplier + initialTime, 0.0f, 1.0f));
}

float TimelineEvent::getTime()
{
	return this->time;
}

void TimelineEvent::setTime(float time)
{
	this->time = time;
}

bool TimelineEvent::tryUpdateEvent(float previousTime, float currentTime)
{
	if (this->isDeactivated)
	{
		return false;
	}
	
	if (previousTime <= this->time && currentTime >= this->time)
	{
		if (this->timelineEvent != nullptr)
		{
			this->timelineEvent();

			return true;
		}
	}

	return false;
}

bool TimelineEvent::isPlayerEntry()
{
	return (dynamic_cast<PlatformerEnemy*>(this->owner) == nullptr);
}
