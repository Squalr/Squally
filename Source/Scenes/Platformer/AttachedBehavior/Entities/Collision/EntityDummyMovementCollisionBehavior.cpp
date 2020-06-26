#include "EntityDummyMovementCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityHeadCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string EntityDummyMovementCollisionBehavior::MapKey = "entity-dummy-movement-collisions";

EntityDummyMovementCollisionBehavior* EntityDummyMovementCollisionBehavior::create(GameObject* owner)
{
	EntityDummyMovementCollisionBehavior* instance = new EntityDummyMovementCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityDummyMovementCollisionBehavior::EntityDummyMovementCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->movementCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->movementCollision = CollisionObject::create(
			CollisionObject::createBox(this->entity->getEntitySize()),
			CollisionType(PlatformerCollisionType::None),
			CollisionObject::Properties(false, false),
			Color4F::BLUE
		);

		Vec2 collisionOffset = this->entity->getCollisionOffset();
		Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);

		this->movementCollision->setPosition(offset);
		this->movementCollision->setPhysicsEnabled(false);

		this->addChild(this->movementCollision);
	}
}

EntityDummyMovementCollisionBehavior::~EntityDummyMovementCollisionBehavior()
{
}

void EntityDummyMovementCollisionBehavior::onLoad()
{
}

void EntityDummyMovementCollisionBehavior::onDisable()
{
	super::onDisable();
}

void EntityDummyMovementCollisionBehavior::buildMovementCollision()
{
}
