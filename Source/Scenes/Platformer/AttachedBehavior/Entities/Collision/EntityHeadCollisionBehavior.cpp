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
const float EntityHeadCollisionBehavior::HeadCollisionSize = 48.0f;

EntityHeadCollisionBehavior* EntityHeadCollisionBehavior::create(GameObject* owner)
{
	EntityHeadCollisionBehavior* instance = new EntityHeadCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityHeadCollisionBehavior::EntityHeadCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->headCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);
}

EntityHeadCollisionBehavior::~EntityHeadCollisionBehavior()
{
}

void EntityHeadCollisionBehavior::onLoad()
{
	this->defer([=]()
	{
		this->buildHeadCollisionDetector();
		this->toggleQueryable(true);
	});
}

void EntityHeadCollisionBehavior::onDisable()
{
	super::onDisable();
	
	if (this->headCollision != nullptr)
	{
		this->headCollision->setPhysicsEnabled(false);
	}
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
			case (int)PlatformerCollisionType::SolidRoof:
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

void EntityHeadCollisionBehavior::buildHeadCollisionDetector()
{
	if (this->headCollision != nullptr)
	{
		return;
	}
	
	this->headCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(
			Size(std::max((this->entity->getEntitySize()).width + EntityHeadCollisionBehavior::HeadCollisionPadding * 2.0f, 8.0f), EntityHeadCollisionBehavior::HeadCollisionSize)
		),
		(int)PlatformerCollisionType::HeadDetector,
		CollisionObject::Properties(false, false),
		Color4F::YELLOW
	);

	Vec2 entityCenter = this->entity->getEntityCenterPoint();
	Vec2 offset = entityCenter + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);

	this->headCollision->setPosition(offset);
	
	this->addChild(this->headCollision);

	this->headCollision->whenCollidesWith({ (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::SolidRoof }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}
