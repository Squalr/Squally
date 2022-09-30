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
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const int EnvelopingWinds::WindDamage = 4;
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
	
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	Sprite* icon = Sprite::create(UIResources::Menus_Icons_Tornado);

	timelineEvents.push_back(TimelineEvent::create(
			this->caster,
			icon,
			0.5f, [=]()
		{
			this->damageOtherTeam();
		})
	);

	CombatEvents::TriggerRegisterTimelineEventGroup(CombatEvents::RegisterTimelineEventGroupArgs(
		TimelineEventGroup::create(timelineEvents, nullptr, this->caster, [=]()
		{
		})
	));
}

void EnvelopingWinds::damageOtherTeam()
{
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
	{
		for (TimelineEntry* next : timeline->getEntries())
		{
			if (!next->isPlayerEntry())
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), std::abs(EnvelopingWinds::WindDamage), AbilityType::Nature, true));
			}
		}
	}));
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
