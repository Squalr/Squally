#include "Punch.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/Sound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

Punch* Punch::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
{
	Punch* instance = new Punch(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

Punch::Punch(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_Punch,
		priority,
		AbilityType::Physical,
		damageMin,
		damageMax,
		0,
		attackDuration,
		recoverDuration
	)
{
	this->punchSound = Sound::create(SoundResources::Platformer_Physical_Punches_Punch7);

	this->addChild(this->punchSound);
}

Punch::~Punch()
{
}

PlatformerAttack* Punch::cloneInternal()
{
	return Punch::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* Punch::getString()
{
	return Strings::Platformer_Combat_Attacks_Punch::create();
}

std::string Punch::getAttackAnimation()
{
	return "AttackPunch";
}

void Punch::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();

	this->punchSound->play(false, this->attackDuration / 2.0f);
}

void Punch::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		this->doDamageOrHealing(owner, next);
	}
}

void Punch::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage(), this->abilityType));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
