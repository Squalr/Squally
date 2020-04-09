#include "FriendlyCombatCollisionBehavior.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string FriendlyCombatCollisionBehavior::MapKey = "friendly-combat-collisions";

FriendlyCombatCollisionBehavior* FriendlyCombatCollisionBehavior::create(GameObject* owner)
{
	FriendlyCombatCollisionBehavior* instance = new FriendlyCombatCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

FriendlyCombatCollisionBehavior::FriendlyCombatCollisionBehavior(GameObject* owner) : super(owner, (CollisionType)CombatCollisionType::EntityFriendly)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

FriendlyCombatCollisionBehavior::~FriendlyCombatCollisionBehavior()
{
}

void FriendlyCombatCollisionBehavior::onLoad()
{
    super::onLoad();
}

void FriendlyCombatCollisionBehavior::onDisable()
{
	super::onDisable();
}

void FriendlyCombatCollisionBehavior::onEntityCollisionCreated()
{
}
