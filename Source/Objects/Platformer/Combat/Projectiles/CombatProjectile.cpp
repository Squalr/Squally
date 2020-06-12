#include "CombatProjectile.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Events/CombatEvents.h"

using namespace cocos2d;

CombatProjectile::CombatProjectile(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, std::vector<cocos2d::Vec2> hitBox, int collisionType, bool allowHacking)
	: super(caster, hitBox, collisionType, allowHacking)
{
	this->target = target;
	this->timelinePaused = false;
	this->timelinePausedCinematic = false;
	this->onTimeline = onTimeline;
}

CombatProjectile::~CombatProjectile()
{
}

void CombatProjectile::onEnter()
{
	super::onEnter();

	CombatEvents::TriggerProjectileSpawned(CombatEvents::ProjectileSpawnedArgs(this->caster, target, this));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimeline, [=](EventCustom* eventCustom)
	{
		this->timelinePaused = true;
		
		this->updateProjectileCanUpdate();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimeline, [=](EventCustom* eventCustom)
	{
		this->timelinePaused = false;
		
		this->updateProjectileCanUpdate();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->timelinePausedCinematic = true;
		
		this->updateProjectileCanUpdate();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->timelinePausedCinematic = false;

		this->updateProjectileCanUpdate();
	}));
}
	
void CombatProjectile::updateProjectileCanUpdate()
{
	if (this->onTimeline)
	{
		if (this->timelinePaused || this->timelinePausedCinematic)
		{
			this->disableUpdate();
		}
		else
		{
			this->enableUpdate();
		}
	}
}
