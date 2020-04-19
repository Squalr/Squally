#include "MultiShot.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float MultiShot::DamageMultiplier = 0.75f;

MultiShot* MultiShot::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
{
	MultiShot* instance = new MultiShot(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

MultiShot::MultiShot(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_ArcheryTarget,
		priority,
		damageMin,
		damageMax,
		8,
		attackDuration,
		recoverDuration,
		true
	)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Projectiles_WeaponThrow1);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Impact_HitSoft1);

	this->setDamageMultiplier(MultiShot::DamageMultiplier);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

MultiShot::~MultiShot()
{
}

PlatformerAttack* MultiShot::cloneInternal()
{
	return MultiShot::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* MultiShot::getString()
{
	return Strings::Platformer_Combat_Attack::create(); // No string yet! (choose an arbitrary placeholder)
}

std::string MultiShot::getAttackAnimation()
{
	return "AttackShoot";
}

void MultiShot::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	// Sound will be changed out later
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void MultiShot::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		this->doDamageOrHealing(owner, next);
	}
}

void MultiShot::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
