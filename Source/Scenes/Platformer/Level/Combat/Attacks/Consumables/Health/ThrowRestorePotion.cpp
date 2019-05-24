#include "ThrowRestorePotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Consumables/Health/ProjectileRestorePotion.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Empty.h"

using namespace cocos2d;

ThrowRestorePotion* ThrowRestorePotion::create()
{
	ThrowRestorePotion* instance = new ThrowRestorePotion();

	instance->autorelease();

	return instance;
}

ThrowRestorePotion::ThrowRestorePotion() : super(AttackType::ProjectileHealing, UIResources::Menus_Objects_HEALTH_2, 0.5f, 10, 15, 0, 0.2f, 1.5f)
{
}

ThrowRestorePotion::~ThrowRestorePotion()
{
}

PlatformerAttack* ThrowRestorePotion::clone()
{
	return ThrowRestorePotion::create();
}

LocalizedString* ThrowRestorePotion::getString()
{
	return Strings::Generics_Empty::create();
}

std::string ThrowRestorePotion::getAttackAnimation()
{
	return "Throw";
}

void ThrowRestorePotion::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);

	ProjectileRestorePotion* potion = ProjectileRestorePotion::create();

	this->replaceWeaponWithProjectile(owner, potion);

	potion->launchTowardsTarget(owner, Vec2(0.0f, owner->getEntitySize().height / 2.0f) + Vec2(0.0f, 256.0f), 0.25f, Vec3(5.0f, 0.75f, 0.75f));
}

void ThrowRestorePotion::onCleanup()
{
}
