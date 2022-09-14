#include "CastRockSlide.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/RockSlide/RockSlide.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastRockSlide* CastRockSlide::create(float attackDuration, float recoverDuration, Priority priority, std::string rockResource)
{
	CastRockSlide* instance = new CastRockSlide(attackDuration, recoverDuration, priority, rockResource);

	instance->autorelease();

	return instance;
}

CastRockSlide::CastRockSlide(float attackDuration, float recoverDuration, Priority priority, std::string rockResource)
	: super(AttackType::Damage, UIResources::Menus_Icons_RocksDark, priority, AbilityType::Physical, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Multi)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	this->rockResource = rockResource;
	
	this->addChild(this->castSound);
}

CastRockSlide::~CastRockSlide()
{
}

void CastRockSlide::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastRockSlide::cloneInternal()
{
	return CastRockSlide::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority, this->rockResource);
}

LocalizedString* CastRockSlide::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_RockSlide_RockSlide::create();
}

std::string CastRockSlide::getAttackAnimation()
{
	return "AttackCast";
}

void CastRockSlide::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	this->castSound->play();
	owner->getAnimations()->clearAnimationPriority();
	owner->getAnimations()->playAnimation(this->getAttackAnimation());

	ObjectEvents::QueryObject<CinematicMarker>([=](CinematicMarker* marker)
	{
		RockSlide* rockRain = RockSlide::create(owner, nullptr, this->rockResource);

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			marker,
			rockRain,
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
		rockRain->setPosition(rockRain->getPosition() + Vec2(0.0f, 512.0f));
	},
	PlatformerAttack::TagArenaTop,
	[=]()
	{
		// TOP CENTER ARENA MARKER NOT FOUND!
		RockSlide* rockRain = RockSlide::create(owner, nullptr, this->rockResource);

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			this,
			rockRain,
			SpawnMethod::Above,
			PositionMode::SetToOwner,
			[&]()
			{
			},
			[&]()
			{
			}
		));
		
		// Fall back by spawning the rock rain in a quasi reasonable spot.
		rockRain->setPosition(rockRain->getPosition() + Vec2(-256.0f, 1024.0f));
	});
}

void CastRockSlide::onCleanup()
{
}

bool CastRockSlide::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	bool worthUsing = true;
	
	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (auto next : timeline->getEntries())
		{
			if (dynamic_cast<CastRockSlide*>(next->getStagedCast()) != nullptr)
			{
				worthUsing = false;
				break;
			}
		}
	}));

	ObjectEvents::QueryObject<RockSlide>([&](RockSlide*)
	{
		worthUsing = false;
	});

	return worthUsing;
}

float CastRockSlide::getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return 1.0;
}
