#include "Pound.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/Sound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float Pound::DamageMultiplier = 1.5f;

Pound* Pound::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
{
	Pound* instance = new Pound(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

Pound::Pound(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_PunchStrong,
		priority,
		AbilityType::Physical,
		damageMin,
		damageMax,
		5,
		attackDuration,
		recoverDuration
	)
{
	this->punchSound = Sound::create(SoundResources::Platformer_Physical_Punches_Punch7);

	this->setDamageMultiplier(Pound::DamageMultiplier);

	this->addChild(this->punchSound);
}

Pound::~Pound()
{
}

PlatformerAttack* Pound::cloneInternal()
{
	return Pound::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* Pound::getString()
{
	return Strings::Platformer_Combat_Attacks_Pound::create();
}

std::string Pound::getAttackAnimation()
{
	return "AttackPunch";
}

void Pound::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();

	this->punchSound->play(false, this->attackDuration / 2.0f);
}

void Pound::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		this->doDamageOrHealing(owner, next);
	}
}

void Pound::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage(), this->abilityType));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
