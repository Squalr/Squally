#include "TimelineEntry.h"

#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/UI/Controls/CProgressBar.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Attacks/PlatformerAttack.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float TimelineEntry::CastPercentage = 0.8f;

TimelineEntry* TimelineEntry::create(PlatformerEntity* entity, bool isPlayerEntry)
{
	TimelineEntry* instance = new TimelineEntry(entity, isPlayerEntry);

	instance->autorelease();

	return instance;
}

TimelineEntry::TimelineEntry(PlatformerEntity* entity, bool isPlayerEntry)
{
	this->entity = entity;
	this->line = Sprite::create(UIResources::Combat_Line);
	this->circle = isPlayerEntry ? Sprite::create(UIResources::Combat_PlayerCircle) : Sprite::create(UIResources::Combat_EnemyCircle);
	this->emblem = Sprite::create(entity->getEmblemResource());

	this->isPlayerEntry = isPlayerEntry;

	this->speed = 1.0f;
	this->progress = 0.0f;

	this->addChild(this->line);
	this->addChild(this->circle);
	this->addChild(this->emblem);
}

void TimelineEntry::onEnter()
{
	super::onEnter();

	this->currentCast = nullptr;
	this->target = nullptr;

	this->scheduleUpdate();
}

void TimelineEntry::initializePositions()
{
	super::initializePositions();

	const float EntryOffsetY = 72.0f;
	const float LineOffsetY = 48.0f;

	if (this->isPlayerEntry)
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

void TimelineEntry::initializeListeners()
{
	super::initializeListeners();
}

void TimelineEntry::update(float dt)
{
	super::update(dt);
}

PlatformerEntity* TimelineEntry::getEntity()
{
	return this->entity;
}

void TimelineEntry::defend()
{

}

bool TimelineEntry::isPlayerTimelineEntry()
{
	return this->isPlayerEntry;
}

bool TimelineEntry::isCasting()
{
	return this->progress > TimelineEntry::CastPercentage;
}

void TimelineEntry::stageTarget(PlatformerEntity* target)
{
	this->target = target;
}

void TimelineEntry::stageCast(PlatformerAttack* attack)
{
	this->currentCast = attack;
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
		if (this->entity != nullptr && this->currentCast != nullptr && this->target != nullptr)
		{
			CombatEvents::TriggerPauseTimeline();

			this->entity->castAttack(this->currentCast, this->target, [=](PlatformerEntity::CastResult result)
			{
				this->progress = std::fmod(this->progress, 1.0f);

				CombatEvents::TriggerDamageDelt(CombatEvents::DamageDeltArgs(result.damageDelta, this->target));
				CombatEvents::TriggerResumeTimeline();
			});
		}
		else
		{
			this->progress = std::fmod(this->progress, 1.0f);
		}
	}
	// Cast started
	else if (!wasCasting && this->isCasting())
	{
		if (this->isPlayerEntry)
		{
			CombatEvents::TriggerPauseTimeline();
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this));
		}
		else
		{
			CombatEvents::TriggerPauseTimeline();
			CombatEvents::TriggerRequestAIAction(CombatEvents::AIRequestArgs(this));
		}
	}

	return this->progress;
}

float TimelineEntry::getSpeed()
{
	return this->speed;
}
