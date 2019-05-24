#include "TorchThrow.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/BomberTorch/BomberTorch.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Empty.h"

using namespace cocos2d;

TorchThrow* TorchThrow::create(float attackDuration, float recoverDuration)
{
	TorchThrow* instance = new TorchThrow(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

TorchThrow::TorchThrow(float attackDuration, float recoverDuration) : super(AttackType::ProjectileDamage, UIResources::Menus_Icons_FireBalls, 0.5f, -3, -5, 0, attackDuration, recoverDuration)
{
}

PlatformerAttack* TorchThrow::clone()
{
	return TorchThrow::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* TorchThrow::getString()
{
	return Strings::Generics_Empty::create();
}

void TorchThrow::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);

	BomberTorch* torch = BomberTorch::create(this->getRandomDamageOrHealing());
	AnimationPart* weapon = owner->getAnimations()->getAnimationPart("mainhand");

	if (weapon != nullptr)
	{
		weapon->replaceWithObject(torch, 2.0f);
	}

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		owner,
		torch,
		ObjectEvents::SpawnMethod::Below
	));

	torch->launchTowardsTarget(target, Vec2(0.0f, target->getEntitySize().height / 2.0f), 2.0f, Vec3(0.5f, 0.5f, 0.5f));
}

void TorchThrow::onCleanup()
{
}
