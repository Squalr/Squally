#include "CastDistract.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Defend/Defend.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastDistract* CastDistract::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastDistract* instance = new CastDistract(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastDistract::CastDistract(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Defensive,
		UIResources::Menus_Icons_Bell,
		priority,
		AbilityType::Physical,
		0,
		0,
		4,
		attackDuration,
		recoverDuration,
		TargetingType::Self
	)
{
	this->defendSound = WorldSound::create(SoundResources::Platformer_Defense_Rebound2);

	this->addChild(this->defendSound);
}

CastDistract::~CastDistract()
{
}

PlatformerAttack* CastDistract::cloneInternal()
{
	return CastDistract::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastDistract::getString()
{
	return Strings::Platformer_Combat_Defensives_Distract::create();
}

LocalizedString* CastDistract::getDescription()
{
	return Strings::Platformer_Combat_Defensives_DistractDescription::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create() });
}

std::string CastDistract::getAttackAnimation()
{
	return "AttackCast";
}

void CastDistract::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	this->defendSound->play(false, 0.0f);

	owner->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Defend::create(owner, true));
		
		CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
		{
			for (TimelineEntry* next : timeline->getEnemyEntries())
			{
				CombatEvents::TriggerRequestRetargetReevalutation(CombatEvents::AIRequestArgs(next));
			}
		}));
	});
}
