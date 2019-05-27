#include "Punch.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Attacks/Punch.h"

using namespace cocos2d;

Punch* Punch::create(float attackDuration, float recoverDuration)
{
	Punch* instance = new Punch(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

Punch::Punch(float attackDuration, float recoverDuration) : super(AttackType::Damage, UIResources::Menus_Icons_Punch, 0.5f, -3, -5, 0, attackDuration, recoverDuration)
{
}

PlatformerAttack* Punch::clone()
{
	return Punch::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* Punch::getString()
{
	return Strings::Combat_Attacks_Punch::create();
}

std::string Punch::getAttackAnimation()
{
	return "AttackPunch";
}

void Punch::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamageOrHealing()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
