#include "BasicSlash.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Attacks/Basic/BasicSlash.h"

using namespace cocos2d;

BasicSlash* BasicSlash::create(float attackDuration, float recoverDuration)
{
	BasicSlash* instance = new BasicSlash(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

BasicSlash::BasicSlash(float attackDuration, float recoverDuration) : super(AttackType::Direct, UIResources::Menus_Icons_SwordSlash, 3, 5, 0, attackDuration, recoverDuration)
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
