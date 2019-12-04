#include "ThrowWeapon.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/ThrownWeapon/ThrownWeapon.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowWeapon* ThrowWeapon::create(float attackDuration, float recoverDuration)
{
	ThrowWeapon* instance = new ThrowWeapon(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

ThrowWeapon::ThrowWeapon(float attackDuration, float recoverDuration) : super(AttackType::ProjectileDamage, UIResources::Menus_Icons_FireBalls, 0.5f, -3, -5, 0, attackDuration, recoverDuration)
{
}

ThrowWeapon::~ThrowWeapon()
{
}

PlatformerAttack* ThrowWeapon::cloneInternal()
{
	return ThrowWeapon::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* ThrowWeapon::getString()
{
	return Strings::Common_Empty::create();
}

std::string ThrowWeapon::getAttackAnimation()
{
	return "AttackThrow";
}

void ThrowWeapon::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);

	ThrownWeapon* weapon = ThrownWeapon::create(owner, this->getMainhandResource(owner), this->getRandomDamageOrHealing());

	this->replaceMainhandWithProjectile(owner, weapon);

	weapon->launchTowardsTarget(target, Vec2(0.0f, target->getEntitySize().height / 2.0f), 2.0f, Vec3(0.5f, 0.5f, 0.5f));
}

void ThrowWeapon::onCleanup()
{
}
