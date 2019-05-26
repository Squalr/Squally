#include "BasicSlash.h"

#include "Events/CombatEvents.h"
#include "Engine/Camera/GameCamera.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Attacks/Basic/BasicSlash.h"

using namespace cocos2d;

BasicSlash* BasicSlash::create(float attackDuration, float recoverDuration)
{
	BasicSlash* instance = new BasicSlash(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

BasicSlash::BasicSlash(float attackDuration, float recoverDuration) : super(AttackType::Damage, UIResources::Menus_Icons_SwordSlash, 0.5f, -3, -5, 0, attackDuration, recoverDuration)
{
}

PlatformerAttack* BasicSlash::clone()
{
	return BasicSlash::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* BasicSlash::getString()
{
	return Strings::Combat_Attacks_Basic_BasicSlash::create();
}

void BasicSlash::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
	CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, target, this->getRandomDamageOrHealing()));

	GameCamera::getInstance()->shakeCamera(0.2f, 12.0f, 0.3f);
}
