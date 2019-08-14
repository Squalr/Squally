#include "TorchThrow.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/BomberTorch/BomberTorch.h"

#include "Resources/UIResources.h"

#include "Strings/Common/Empty.h"

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

TorchThrow::~TorchThrow()
{
}

PlatformerAttack* TorchThrow::cloneInternal()
{
	return TorchThrow::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* TorchThrow::getString()
{
	return Strings::Common_Empty::create();
}

std::string TorchThrow::getAttackAnimation()
{
	return "AttackThrow";
}

void TorchThrow::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);

	BomberTorch* torch = BomberTorch::create(owner, this->getRandomDamageOrHealing());

	this->replaceMainhandWithProjectile(owner, torch);

	torch->launchTowardsTarget(target, Vec2(0.0f, target->getEntitySize().height / 2.0f), 2.0f, Vec3(0.5f, 0.5f, 0.5f));
}

void TorchThrow::onCleanup()
{
}
