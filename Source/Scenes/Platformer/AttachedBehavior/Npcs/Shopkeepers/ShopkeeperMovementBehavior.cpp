#include "ShopkeeperMovementBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string ShopkeeperMovementBehavior::MapKeyAttachedBehavior = "shopkeeper-movements";

ShopkeeperMovementBehavior* ShopkeeperMovementBehavior::create(GameObject* owner)
{
	ShopkeeperMovementBehavior* instance = new ShopkeeperMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

ShopkeeperMovementBehavior::ShopkeeperMovementBehavior(GameObject* owner) : super(owner)
{
	this->npc = dynamic_cast<PlatformerFriendly*>(owner);

	if (this->npc == nullptr)
	{
		this->invalidate();
	}

	this->squally = nullptr;
}

ShopkeeperMovementBehavior::~ShopkeeperMovementBehavior()
{
}

void ShopkeeperMovementBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, &this->squally);
}

void ShopkeeperMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr)
	{
		return;
	}

	if (this->npc->getPositionX() > this->squally->getPositionX())
	{
		this->npc->getAnimations()->setFlippedX(true);
	}
	else
	{
		this->npc->getAnimations()->setFlippedX(false);
	}
}
