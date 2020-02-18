#include "EntityJumpCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityJumpCollisionBehavior::MapKeyAttachedBehavior = "entity-jump-collisions";
const float EntityJumpCollisionBehavior::JumpCollisionMargin = 8.0f;
const float EntityJumpCollisionBehavior::JumpCollisionOffset = -4.0f;
const float EntityJumpCollisionBehavior::JumpCollisionHeight = 48.0f;

EntityJumpCollisionBehavior* EntityJumpCollisionBehavior::create(GameObject* owner)
{
	EntityJumpCollisionBehavior* instance = new EntityJumpCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityJumpCollisionBehavior::EntityJumpCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->jumpCollision = nullptr;
	
	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);
}

EntityJumpCollisionBehavior::~EntityJumpCollisionBehavior()
{
}

void EntityJumpCollisionBehavior::onLoad()
{
	this->defer([=]()
	{
		this->buildJumpCollisionDetector();
		this->toggleQueryable(true);
	});
}

bool EntityJumpCollisionBehavior::canJump()
{
	for (auto collision : this->jumpCollision->getCurrentCollisions())
	{
		if (collision->getCollisionType() == (int)PlatformerCollisionType::Solid
			|| collision->getCollisionType() == (int)PlatformerCollisionType::Physics
			|| collision->getCollisionType() == (int)PlatformerCollisionType::PassThrough)
		{
			return true;	
		}
	}

	return false;
}

void EntityJumpCollisionBehavior::buildJumpCollisionDetector()
{
	if (this->jumpCollision != nullptr)
	{
		return;
	}
	
	this->jumpCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(
			Size(std::max((this->entity->getEntitySize()).width - EntityJumpCollisionBehavior::JumpCollisionMargin * 2.0f, 8.0f), EntityJumpCollisionBehavior::JumpCollisionHeight)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::YELLOW
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();

	if (this->entity->isFlippedY())
	{
		Vec2 offset = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(0.0f, -this->entity->getHoverHeight() / 2.0f - EntityJumpCollisionBehavior::JumpCollisionOffset);
		this->jumpCollision->inverseGravity();
		this->jumpCollision->setPosition(offset);
	}
	else
	{
		Vec2 offset = collisionOffset + Vec2(0.0f, -this->entity->getHoverHeight() / 2.0f + EntityJumpCollisionBehavior::JumpCollisionOffset);
		this->jumpCollision->setPosition(offset);
	}
	
	this->addChild(this->jumpCollision);

	this->jumpCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->jumpCollision->whenStopsCollidingWith({ (int)EngineCollisionTypes::Intersection }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->jumpCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}
