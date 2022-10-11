#include "EnemyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Collision/EnemyCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Collision/EnemyWeaponCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/EnemyCombatEngageBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Stats/EnemyHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"

using namespace cocos2d;

const std::string EnemyBehaviorGroup::MapKey = "enemy";

EnemyBehaviorGroup* EnemyBehaviorGroup::create(GameObject* owner)
{
	EnemyBehaviorGroup* instance = new EnemyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EnemyBehaviorGroup::EnemyBehaviorGroup(GameObject* owner) : super(owner, {
	EntityBehaviorGroup::create(owner),
	EntityInventoryBehavior::create(owner),
	EnemyCollisionBehavior::create(owner),
	EnemyWeaponCollisionBehavior::create(owner),
	EnemyHealthBehavior::create(owner),
	EnemyCombatEngageBehavior::create(owner),
	})
{
}

EnemyBehaviorGroup::~EnemyBehaviorGroup()
{
}

void EnemyBehaviorGroup::onLoad()
{
}
