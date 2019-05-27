#include "ThrowHealthPotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Consumables/Health/ProjectileHealthPotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Generics/Empty.h"

using namespace cocos2d;

ThrowHealthPotion* ThrowHealthPotion::create()
{
	ThrowHealthPotion* instance = new ThrowHealthPotion();

	instance->autorelease();

	return instance;
}

ThrowHealthPotion::ThrowHealthPotion() : super(AttackType::ProjectileHealing, ObjectResources::Items_Consumables_HEALTH_2, 0.5f, 10, 15, 0, 0.2f, 1.5f)
{
}

ThrowHealthPotion::~ThrowHealthPotion()
{
}

PlatformerAttack* ThrowHealthPotion::clone()
{
	return ThrowHealthPotion::create();
}

LocalizedString* ThrowHealthPotion::getString()
{
	return Strings::Generics_Empty::create();
}

std::string ThrowHealthPotion::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowHealthPotion::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);
	
	ProjectileHealthPotion* potion = ProjectileHealthPotion::create(owner);

	this->replaceOffhandWithProjectile(owner, potion);

	potion->launchTowardsTarget(owner, Vec2(0.0f, owner->getEntitySize().height / 2.0f) + Vec2(0.0f, 256.0f), 0.25f, Vec3(5.0f, 0.75f, 0.75f));
}

void ThrowHealthPotion::onCleanup()
{
}
