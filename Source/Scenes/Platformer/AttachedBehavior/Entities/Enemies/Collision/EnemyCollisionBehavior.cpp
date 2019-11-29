#include "EnemyCollisionBehavior.h"

using namespace cocos2d;

const std::string EnemyCollisionBehavior::MapKeyAttachedBehavior = "enemy-collisions";

EnemyCollisionBehavior* EnemyCollisionBehavior::create(GameObject* owner)
{
	EnemyCollisionBehavior* instance = new EnemyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyCollisionBehavior::EnemyCollisionBehavior(GameObject* owner) : super(owner, PlatformerCollisionType::Enemy)
{
}

EnemyCollisionBehavior::~EnemyCollisionBehavior()
{
}
