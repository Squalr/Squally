#include "EnemyCombatCollisionBehavior.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string EnemyCombatCollisionBehavior::MapKey = "enemy-combat-collisions";

EnemyCombatCollisionBehavior* EnemyCombatCollisionBehavior::create(GameObject* owner)
{
	EnemyCombatCollisionBehavior* instance = new EnemyCombatCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyCombatCollisionBehavior::EnemyCombatCollisionBehavior(GameObject* owner) : super(owner, (int)CombatCollisionType::EntityEnemy)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EnemyCombatCollisionBehavior::~EnemyCombatCollisionBehavior()
{
}

void EnemyCombatCollisionBehavior::onLoad()
{
    super::onLoad();
}

void EnemyCombatCollisionBehavior::onDisable()
{
	super::onDisable();
}

void EnemyCombatCollisionBehavior::onEntityCollisionCreated()
{
}
