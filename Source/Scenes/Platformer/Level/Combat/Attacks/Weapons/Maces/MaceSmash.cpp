#include "MaceSmash.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float MaceSmash::DamageMultiplier = 1.4f;

MaceSmash* MaceSmash::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
{
	MaceSmash* instance = new MaceSmash(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

MaceSmash::MaceSmash(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority)
	: super(
		AttackType::Damage,
		UIResources::Menus_Icons_MaceStrike, priority,
		damageMin,
		damageMax,
		6,
		attackDuration,
		recoverDuration
	)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_SwingBlade2);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Impact_HitSoft1);

	this->setDamageMultiplier(MaceSmash::DamageMultiplier);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

MaceSmash::~MaceSmash()
{
}

PlatformerAttack* MaceSmash::cloneInternal()
{
	return MaceSmash::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* MaceSmash::getString()
{
	return Strings::Platformer_Combat_Attacks_Smash::create();
}

std::string MaceSmash::getAttackAnimation()
{
	return "AttackSlash";
}

void MaceSmash::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void MaceSmash::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		this->doDamageOrHealing(owner, next);
	}
}

void MaceSmash::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
