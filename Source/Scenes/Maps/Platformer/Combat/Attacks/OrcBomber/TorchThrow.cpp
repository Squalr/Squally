#include "TorchThrow.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Engine/Events/SpawnEvents.h"
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

	SpawnEvents::TriggerObjectSpawn(SpawnEvents::RequestObjectSpawnArgs(
		owner,
		BomberTorch::create(),
		owner->getPosition3D() + Vec3(0.0f, 64.0f, 0.0f),
		SpawnEvents::SpawnMethod::Below
	));
}
