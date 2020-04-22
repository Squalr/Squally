#include "EnemyBattleAllyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Ally/EnemyAllyDropBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Ally/EnemyAllyVisibilityBehavior.h"

using namespace cocos2d;

const std::string EnemyBattleAllyBehaviorGroup::MapKey = "ally";

EnemyBattleAllyBehaviorGroup* EnemyBattleAllyBehaviorGroup::create(GameObject* owner)
{
	EnemyBattleAllyBehaviorGroup* instance = new EnemyBattleAllyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EnemyBattleAllyBehaviorGroup::EnemyBattleAllyBehaviorGroup(GameObject* owner) : super(owner, {
	EnemyAllyDropBehavior::create(owner),
	EnemyAllyVisibilityBehavior::create(owner),
	})
{
}

EnemyBattleAllyBehaviorGroup::~EnemyBattleAllyBehaviorGroup()
{
}

void EnemyBattleAllyBehaviorGroup::onLoad()
{
}
