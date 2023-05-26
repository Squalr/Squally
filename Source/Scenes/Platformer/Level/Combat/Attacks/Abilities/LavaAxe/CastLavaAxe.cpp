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

		for (PlatformerEntity* target : targets)
		{
			LavaAxe* lavaAxe = LavaAxe::create(owner, nullptr, [=](int damage)
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, damage, this->abilityType));
			});

			TimelineEntry* entry = timeline->getAssociatedEntry(target);
			
			ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
				target,
				lavaAxe,
				SpawnMethod::Above,
				PositionMode::Discard,
				[&]()
				{
				},
				[&]()
				{
				}
			));
			
			GameUtils::setWorldCoords3D(lavaAxe, GameUtils::getWorldCoords3D(target, false) + Vec3(0.0f, this->owner->getEntityTopPointRelative().y + 48.0f, 0.0f));
			lavaAxe->runLavaAxe(entry);
		}
	}));
}

void CastLavaAxe::onCleanup()
{
}
