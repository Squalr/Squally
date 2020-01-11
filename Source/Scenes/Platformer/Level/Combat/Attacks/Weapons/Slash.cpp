#include "Slash.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Sound/WorldSound.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

Slash* Slash::create(float attackDuration, float recoverDuration, float priority)
{
	Slash* instance = new Slash(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

Slash::Slash(float attackDuration, float recoverDuration, float priority) : super(AttackType::Damage, UIResources::Menus_Icons_SwordSlash, priority, 3, 5, 0, attackDuration, recoverDuration)
{
	this->slashSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Swings_Swing1);
	this->hitSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Impact_HitSoft1);

	this->addChild(this->slashSound);
	this->addChild(this->hitSound);
}

PlatformerAttack* Slash::cloneInternal()
{
	return Slash::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* Slash::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string Slash::getAttackAnimation()
{
	return "Attack";
}

void Slash::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->slashSound->play(false, this->attackDuration / 2.0f);
}

void Slash::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->doDamageOrHealing(owner, target);
}

void Slash::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	this->hitSound->play();
	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamage()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
