#include "EntityJumpCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityHoverCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityJumpCollisionBehavior::MapKey = "entity-jump-collisions";
const float EntityJumpCollisionBehavior::JumpCollisionMargin = 24.0f;
const float EntityJumpCollisionBehavior::JumpCollisionOffset = 0.0f;
const float EntityJumpCollisionBehavior::JumpCollisionHeight = 64.0f;

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
	this->hoverCollisionBehavior = nullptr;
	
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
	this->entity->watchForComponent<EntityHoverCollisionBehavior>([=](EntityHoverCollisionBehavior* hoverCollisionBehavior)
	{
		this->hoverCollisionBehavior = hoverCollisionBehavior;
	});

	this->defer([=]()
	{
		this->buildJumpCollisionDetector();
		this->toggleQueryable(true);
	});
}

void EntityJumpCollisionBehavior::onDisable()
{
	super::onDisable();
	
	if (this->jumpCollision != nullptr)
	{
		this->jumpCollision->setPhysicsEnabled(false);
	}
}

CollisionObject* EntityJumpCollisionBehavior::getJumpCollision()
{
	return this->jumpCollision;
}

bool EntityJumpCollisionBehavior::canJump()
{
	return this->jumpCollision == nullptr ? false : this->jumpCollision->hasCollisions();
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
		(int)PlatformerCollisionType::JumpDetector,
		CollisionObject::Properties(false, false),
		Color4F::YELLOW
	);
	
	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, EntityJumpCollisionBehavior::JumpCollisionOffset);

	this->jumpCollision->setPosition(offset);
	
	this->addChild(this->jumpCollision);

	this->jumpCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});
}
