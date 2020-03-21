#include "AxeSwing.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AxeSwing* AxeSwing::create(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority)
{
	AxeSwing* instance = new AxeSwing(damageMin, damageMax, attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

AxeSwing::AxeSwing(int damageMin, int damageMax, float attackDuration, float recoverDuration, float priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_Axe, priority, damageMin, damageMax, 0, attackDuration, recoverDuration)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_Swing1);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Impact_HitSoft1);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

AxeSwing::~AxeSwing()
{
}

PlatformerAttack* AxeSwing::cloneInternal()
{
	return AxeSwing::create(this->getBaseDamageMin(), this->getBaseDamageMax(), this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* AxeSwing::getString()
{
	return Strings::Platformer_Combat_Attack::create(); // No string yet! (choose an arbitrary placeholder)
}

std::string AxeSwing::getAttackAnimation()
{
	return "AttackSlash"; // Keep this the same for now
}

void AxeSwing::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	// Sound will be changed out later
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void AxeSwing::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->doDamageOrHealing(owner, target);
}

void AxeSwing::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
