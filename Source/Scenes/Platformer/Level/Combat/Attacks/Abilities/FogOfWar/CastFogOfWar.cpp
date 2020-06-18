#include "CastFogOfWar.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/FogOfWar/FogOfWar.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Fortitude/Fortitude.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastFogOfWar* CastFogOfWar::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastFogOfWar* instance = new CastFogOfWar(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastFogOfWar::CastFogOfWar(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_Fog, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration, true)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	this->arrowResource = arrowResource;
	
	this->addChild(this->castSound);
}

CastFogOfWar::~CastFogOfWar()
{
}

void CastFogOfWar::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastFogOfWar::cloneInternal()
{
	return CastFogOfWar::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastFogOfWar::getString()
{
	return Strings::Menus_Hacking_Abilities_Buffs_Fortitude_Fortitude::create();
}

std::string CastFogOfWar::getAttackAnimation()
{
	return "AttackCast";
}

void CastFogOfWar::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation("AttackCast");

	ObjectEvents::QueryObject<CinematicMarker>(this, [=](CinematicMarker* marker)
	{
		FogOfWar* fogOfWar = FogOfWar::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
			marker,
			fogOfWar,
			ObjectEvents::SpawnMethod::Above,
			ObjectEvents::PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));
	},
	[=]()
	{
		// TOP CENTER ARENA MARKER NOT FOUND!
		FogOfWar* fogOfWar = FogOfWar::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
			this,
			fogOfWar,
			ObjectEvents::SpawnMethod::Above,
			ObjectEvents::PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));
	}, PlatformerAttack::TagArenaBottom);
}

void CastFogOfWar::onCleanup()
{
}

bool CastFogOfWar::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (auto next : timeline->getEntries())
		{
			if (dynamic_cast<CastFogOfWar*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<FogOfWar>(this, [&](FogOfWar*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastFogOfWar::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
