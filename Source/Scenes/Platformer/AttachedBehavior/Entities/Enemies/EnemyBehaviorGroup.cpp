#include "EnemyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Collision/EnemyCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Stats/EnemyHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"

using namespace cocos2d;

const std::string EnemyBehaviorGroup::MapKeyAttachedBehavior = "enemy";

EnemyBehaviorGroup* EnemyBehaviorGroup::create(GameObject* owner)
{
	EnemyBehaviorGroup* instance = new EnemyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EnemyBehaviorGroup::EnemyBehaviorGroup(GameObject* owner) : super(owner, {
	EnemyCollisionBehavior::create(owner),
	EntityBehaviorGroup::create(owner),
	EnemyHealthBehavior::create(owner),
	})
{
}

EnemyBehaviorGroup::~EnemyBehaviorGroup()
{
}

void EnemyBehaviorGroup::onLoad()
{
}
