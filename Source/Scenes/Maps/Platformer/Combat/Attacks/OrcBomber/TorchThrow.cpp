#include "TorchThrow.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/SpawnEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/BomberTorch.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/Empty.h"

using namespace cocos2d;

TorchThrow* TorchThrow::create(float attackDuration, float recoverDuration)
{
	TorchThrow* instance = new TorchThrow(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

TorchThrow::TorchThrow(float attackDuration, float recoverDuration) : super(AttackType::Projectile, UIResources::Menus_Icons_FireBalls, 3, 5, 0, attackDuration, recoverDuration)
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

void TorchThrow::spawnProjectiles(PlatformerEntity* owner)
{
	super::spawnProjectiles(owner);

	AnimationPart* weapon = owner->getAnimations()->getAnimationPart("WEAPON");
	BomberTorch* torch = BomberTorch::create();

	weapon->setOpacity(0);
	torch->setRotation(weapon->getRotation());
	torch->setPosition3D(GameUtils::getWorldCoords(weapon));

	SpawnEvents::TriggerObjectSpawn(SpawnEvents::RequestObjectSpawnArgs(
		owner,
		torch,
		SpawnEvents::SpawnMethod::Below
	));
}
