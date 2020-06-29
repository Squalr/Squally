#include "CastLightningStrike.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/Spells/LightningStrike/LightningStrike.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CastLightningStrike* CastLightningStrike::create(float attackDuration, float recoverDuration, Priority priority)
{
	CastLightningStrike* instance = new CastLightningStrike(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

CastLightningStrike::CastLightningStrike(float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_Lightning,
		priority,
		AbilityType::Lightning,
		12,
		15,
		6,
		attackDuration,
		recoverDuration,
		TargetingType::Single
	)
{
	this->lightningSound = WorldSound::create(SoundResources::Platformer_Spells_Lightning1);

	this->addChild(this->lightningSound);
}

CastLightningStrike::~CastLightningStrike()
{
}

PlatformerAttack* CastLightningStrike::cloneInternal()
{
	return CastLightningStrike::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* CastLightningStrike::getString()
{
	return Strings::Platformer_Combat_Attacks_LightningStrike::create();
}

std::string CastLightningStrike::getAttackAnimation()
{
	return "AttackCast";
}

void CastLightningStrike::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->lightningSound->play(false, this->attackDuration);
}

void CastLightningStrike::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (auto next : targets)
	{
		CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->owner, next, this->getRandomDamage(), this->abilityType));

		next->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
		{
			entityBuffBehavior->applyBuff(LightningStrike::create(owner, next));
		});
	}
}
