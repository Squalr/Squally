#include "EnvelopingWinds.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Particles/SmartParticles.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/ParticleResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float EnvelopingWinds::WindDrain = -15.0f;

EnvelopingWinds* EnvelopingWinds::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	EnvelopingWinds* instance = new EnvelopingWinds(caster, target);

	instance->autorelease();

	return instance;
}

EnvelopingWinds::EnvelopingWinds(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, true, 1.5f)
{
	this->wind = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_WindStorm);

	this->addChild(this->wind);
}

EnvelopingWinds::~EnvelopingWinds()
{
}

void EnvelopingWinds::onEnter()
{
	super::onEnter();

	this->wind->start();
}

void EnvelopingWinds::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
	super::onModifyTimelineSpeed(speed);

	bool isOnCasterTeam = false;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (auto next : timeline->getSameTeamEntities(this->caster))
		{
			if (next == speed->target)
			{
				isOnCasterTeam = true;
			}
		}
	}));

	if (!isOnCasterTeam)
	{
		(*speed->speed) += EnvelopingWinds::WindDrain;
	}
}
