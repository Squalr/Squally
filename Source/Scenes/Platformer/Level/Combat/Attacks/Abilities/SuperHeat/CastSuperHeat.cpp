#include "CastSuperHeat.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/SuperHeat/SuperHeat.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastSuperHeat* CastSuperHeat::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastSuperHeat* instance = new CastSuperHeat(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastSuperHeat::CastSuperHeat(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_Fire,
		priority,
		AbilityType::Fire,
		8,
		11,
		11,
		attackDuration,
		recoverDuration,
		TargetingType::Multi
	)
{
	this->lightningSound = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->addChild(this->lightningSound);
}

CastSuperHeat::~CastSuperHeat()
{
}

PlatformerAttack* CastSuperHeat::cloneInternal()
{
	return CastSuperHeat::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastSuperHeat::getString()
{
	return Strings::Platformer_Combat_Attacks_SuperHeat::create();
}

LocalizedString* CastSuperHeat::getDescription()
{
	return Strings::Platformer_Combat_Attacks_SuperHeatDescription::create();
}

std::string CastSuperHeat::getAttackAnimation()
{
	return "AttackCast";
}

void CastSuperHeat::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->lightningSound->play(false, this->attackDuration);
}

void CastSuperHeat::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (PlatformerEntity* next : targets)
	{
		CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->owner, next, this->getRandomDamage(), this->abilityType));

		next->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(SuperHeat::create(owner, next));
		});
	}
}
