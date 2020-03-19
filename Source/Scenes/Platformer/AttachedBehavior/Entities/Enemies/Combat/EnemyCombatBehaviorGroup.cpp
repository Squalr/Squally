#include "EnemyCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Combat/EnemyCombatCollisionBehavior.h"

using namespace cocos2d;

const std::string EnemyCombatBehaviorGroup::MapKey = "enemy-combat-group";

EnemyCombatBehaviorGroup* EnemyCombatBehaviorGroup::create(GameObject* owner)
{
	EnemyCombatBehaviorGroup* instance = new EnemyCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EnemyCombatBehaviorGroup::EnemyCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCombatBehaviorGroup::create(owner),
	EnemyCombatCollisionBehavior::create(owner),
	})
{
}

EnemyCombatBehaviorGroup::~EnemyCombatBehaviorGroup()
{
}

void EnemyCombatBehaviorGroup::onLoad()
{
}
