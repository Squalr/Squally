#include "CastBatSwarm.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/BatSwarm/BatSwarm.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastBatSwarm* CastBatSwarm::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastBatSwarm* instance = new CastBatSwarm(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastBatSwarm::CastBatSwarm(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_Bats, priority, AbilityType::Shadow, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Multi)
{
	this->castSound = WorldSound::create(ObjectResources::Traps_Ballista_TILT_1);
	
	this->addChild(this->castSound);
}

CastBatSwarm::~CastBatSwarm()
{
}

void CastBatSwarm::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastBatSwarm::cloneInternal()
{
	return CastBatSwarm::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastBatSwarm::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_BatSwarm_BatSwarm::create();
}

std::string CastBatSwarm::getAttackAnimation()
{
	return "AttackCast";
}

void CastBatSwarm::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	ObjectEvents::QueryObject<CinematicMarker>([=](CinematicMarker* marker)
	{
		BatSwarm* arrowRain = BatSwarm::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			marker,
			arrowRain,
			SpawnMethod::Above,
			PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));

		// Place it quasi off-screen
		arrowRain->setPosition(arrowRain->getPosition() + Vec2(0.0f, 512.0f));
	},
	PlatformerAttack::TagArenaTop,
	[=]()
	{
		// TOP CENTER ARENA MARKER NOT FOUND!
		BatSwarm* arrowRain = BatSwarm::create(owner, nullptr);

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			this,
			arrowRain,
			SpawnMethod::Above,
			PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));
		
		// Fall back by spawning the arrow rain in a quasi reasonable spot.
		arrowRain->setPosition(arrowRain->getPosition() + Vec2(-256.0f, 1024.0f));
	});
}

void CastBatSwarm::onCleanup()
{
}

bool CastBatSwarm::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (TimelineEntry* next : timeline->getEntries())
		{
			if (dynamic_cast<CastBatSwarm*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<BatSwarm>([&](BatSwarm*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastBatSwarm::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
