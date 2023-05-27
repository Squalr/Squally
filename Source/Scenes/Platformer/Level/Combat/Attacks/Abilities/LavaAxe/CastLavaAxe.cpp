#include "CastLavaAxe.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Combat/Abilities/LavaAxe/LavaAxe.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastLavaAxe* CastLavaAxe::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastLavaAxe* instance = new CastLavaAxe(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastLavaAxe::CastLavaAxe(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_AxeGlowOrange, priority, AbilityType::Fire, 0, 0, 4, attackDuration, recoverDuration, TargetingType::Single)
{
	this->castSound = WorldSound::create(SoundResources::Platformer_Spells_Heal5);
	
	this->addChild(this->castSound);
}

CastLavaAxe::~CastLavaAxe()
{
}

void CastLavaAxe::initializePositions()
{
	super::initializePositions();
}

PlatformerAttack* CastLavaAxe::cloneInternal()
{
	return CastLavaAxe::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastLavaAxe::getString()
{
	return Strings::Menus_Hacking_Abilities_Abilities_LavaAxe_LavaAxe::create();
}

std::string CastLavaAxe::getAttackAnimation()
{
	return "AttackCast";
}

void CastLavaAxe::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
	{	
		this->castSound->play();
		owner->getAnimations()->clearAnimationPriority();
		owner->getAnimations()->playAnimation(this->getAttackAnimation());
		
		ObjectEvents::QueryObject<CinematicMarker>([=](CinematicMarker* marker)
		{
			LavaAxe* lavaAxe = LavaAxe::create(owner, nullptr);

			ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
				marker,
				lavaAxe,
				SpawnMethod::Above,
				PositionMode::SetToOwner,
				[&]()
				{
				},
				[&]()
				{
				}
			));
		},
		PlatformerAttack::TagArenaBottom,
		[=]()
		{
			// TOP CENTER ARENA MARKER NOT FOUND!
			LavaAxe* lavaAxe = LavaAxe::create(owner, nullptr);

			ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
				this,
				lavaAxe,
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
			lavaAxe->setPosition(lavaAxe->getPosition() + Vec2(-256.0f, 0.0f));
		});
	}));
}

void CastLavaAxe::onCleanup()
{
}
