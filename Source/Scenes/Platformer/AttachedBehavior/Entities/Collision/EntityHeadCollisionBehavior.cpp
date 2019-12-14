#include "EntityHeadCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityHeadCollisionBehavior::MapKeyAttachedBehavior = "entity-head-collisions";
const float EntityHeadCollisionBehavior::HeadCollisionPadding = 16.0f;
const float EntityHeadCollisionBehavior::HeadCollisionOffset = 16.0f;
const float EntityHeadCollisionBehavior::HeadCollisionRadius = 8.0f;

EntityHeadCollisionBehavior* EntityHeadCollisionBehavior::create(GameObject* owner)
{
	EntityHeadCollisionBehavior* instance = new EntityHeadCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityHeadCollisionBehavior::EntityHeadCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->headCollision = CollisionObject::create(
			CollisionObject::createCapsulePolygon(
				Size(std::max((this->entity->getEntitySize()).width + EntityHeadCollisionBehavior::HeadCollisionPadding * 2.0f, 8.0f), (this->entity->getEntitySize()).height / 2.0f),
				1.0f,
				EntityHeadCollisionBehavior::HeadCollisionRadius,
				0.0f
			),
			(int)PlatformerCollisionType::HeadDetector,
			false,
			false
		);

		Vec2 entityCenter = this->entity->getEntityCenterPoint();

		if (this->entity->isFlippedY())
		{
			Vec2 offset = entityCenter - Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);
			this->headCollision->inverseGravity();
			this->headCollision->getPhysicsBody()->setPositionOffset(offset);
		}
		else
		{
			Vec2 offset = entityCenter + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);
			this->headCollision->getPhysicsBody()->setPositionOffset(offset);
		}
		
		this->addChild(this->headCollision);
	}
}

EntityHeadCollisionBehavior::~EntityHeadCollisionBehavior()
{
}

void EntityHeadCollisionBehavior::onLoad()
{
	this->headCollision->whenCollidesWith({ (int)PlatformerCollisionType::PassThrough, }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

bool EntityHeadCollisionBehavior::hasHeadCollisionWith(CollisionObject* collisonObject)
{
	Node* currentCollisionGroup = collisonObject->getParent();

	for (auto next : this->headCollision->getCurrentCollisions())
	{
		if (next->getParent() != currentCollisionGroup)
		{
			continue;
		}

		switch(next->getCollisionType())
		{
			case (int)PlatformerCollisionType::PassThrough:
			{
				return true;
			}
			default:
			{
				break;
			}
		}
	}

	return false;
}
