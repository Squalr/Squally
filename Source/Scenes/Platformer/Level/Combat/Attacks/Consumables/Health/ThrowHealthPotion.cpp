#include "ThrowHealthPotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/SpawnEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Consumables/Health/ProjectileHealthPotion.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Empty.h"

using namespace cocos2d;

ThrowHealthPotion* ThrowHealthPotion::create()
{
	ThrowHealthPotion* instance = new ThrowHealthPotion();

	instance->autorelease();

	return instance;
}

ThrowHealthPotion::ThrowHealthPotion() : super(AttackType::Projectile, UIResources::Menus_Objects_HEALTH_2, 3, 5, 0, 0.75f, 1.5f)
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

void ThrowHealthPotion::spawnProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::spawnProjectiles(owner, target);

	AnimationPart* weapon = owner->getAnimations()->getAnimationPart("mainhand");
	ProjectileHealthPotion* potion = ProjectileHealthPotion::create(this);

	weapon->replaceWithObject(potion, 2.0f);

	SpawnEvents::TriggerObjectSpawn(SpawnEvents::RequestObjectSpawnArgs(
		owner,
		potion,
		SpawnEvents::SpawnMethod::Below
	));

	potion->launchTowardsTarget(target, Vec2(0.0f, target->getEntitySize().height / 2.0f), 0.25f, Vec3(5.0f, 0.75f, 0.75f), cocos2d::Vec3(0.0f, -768.0f * 3.0f, 0.0f));
}

std::string ThrowHealthPotion::getAttackAnimation()
{
	return "Attack";
}
