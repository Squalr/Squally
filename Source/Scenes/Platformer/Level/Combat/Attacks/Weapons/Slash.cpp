#include "Slash.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Attacks/Slash.h"

using namespace cocos2d;

Slash* Slash::create(float attackDuration, float recoverDuration)
{
	Slash* instance = new Slash(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

Slash::Slash(float attackDuration, float recoverDuration) : super(AttackType::Damage, UIResources::Menus_Icons_SwordSlash, 0.5f, -3, -5, 0, attackDuration, recoverDuration)
{
}

PlatformerAttack* Slash::clone()
{
	return Slash::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* Slash::getString()
{
	return Strings::Combat_Attacks_Slash::create();
}

std::string Slash::getAttackAnimation()
{
	return "Attack";
}

void Slash::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamageOrHealing()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
