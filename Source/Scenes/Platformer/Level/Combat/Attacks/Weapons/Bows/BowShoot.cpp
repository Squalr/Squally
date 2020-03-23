#include "BowShoot.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BowShoot* BowShoot::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority)
{
	BowShoot* instance = new BowShoot(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

BowShoot::BowShoot(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_ArcheryTarget, priority, damageMin, damageMax, 0, attackDuration, recoverDuration)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_Swing1);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Impact_HitSoft1);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

BowShoot::~BowShoot()
{
}

PlatformerAttack* BowShoot::cloneInternal()
{
	return BowShoot::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* BowShoot::getString()
{
	return Strings::Platformer_Combat_Attack::create(); // No string yet! (choose an arbitrary placeholder)
}

std::string BowShoot::getAttackAnimation()
{
	return "AttackShoot";
}

void BowShoot::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	// Sound will be changed out later
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void BowShoot::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->doDamageOrHealing(owner, target);
}

void BowShoot::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
