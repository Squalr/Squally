#include "BasicSlashAxe.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BasicSlashAxe* BasicSlashAxe::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
{
	BasicSlashAxe* instance = new BasicSlashAxe(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

BasicSlashAxe::BasicSlashAxe(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_Axe, priority, AbilityType::Physical, damageMin, damageMax, 0, attackDuration, recoverDuration)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Physical_Swings_SwingBlade1);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Physical_Impact_HitSoft1);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

BasicSlashAxe::~BasicSlashAxe()
{
}

PlatformerAttack* BasicSlashAxe::cloneInternal()
{
	return BasicSlashAxe::create(this->getBaseDamageMin(), getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* BasicSlashAxe::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string BasicSlashAxe::getAttackAnimation()
{
	return "Attack";
}

void BasicSlashAxe::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void BasicSlashAxe::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (auto next : targets)
	{
		this->doDamageOrHealing(owner, next);
	}
}

void BasicSlashAxe::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage(), this->abilityType));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
