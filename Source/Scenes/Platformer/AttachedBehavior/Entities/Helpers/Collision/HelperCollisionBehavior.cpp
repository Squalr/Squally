#include "HelperCollisionBehavior.h"

using namespace cocos2d;

const std::string HelperCollisionBehavior::MapKeyAttachedBehavior = "helper-collisions";

HelperCollisionBehavior* HelperCollisionBehavior::create(GameObject* owner)
{
	HelperCollisionBehavior* instance = new HelperCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

HelperCollisionBehavior::HelperCollisionBehavior(GameObject* owner) : super(owner, PlatformerCollisionType::Helper)
{
}

HelperCollisionBehavior::~HelperCollisionBehavior()
{
}
