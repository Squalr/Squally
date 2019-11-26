#include "EntityPacingBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string EntityPacingBehavior::MapKeyAttachedBehavior = "pacing";
const float EntityPacingBehavior::TravelDistanceMax = 512.0f;
const float EntityPacingBehavior::TravelDistanceMin = 96.0f;

EntityPacingBehavior* EntityPacingBehavior::create(GameObject* owner)
{
	EntityPacingBehavior* instance = new EntityPacingBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityPacingBehavior::EntityPacingBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->anchorPosition = Vec2::ZERO;
	this->destinationDelta = 0.0f;
}

EntityPacingBehavior::~EntityPacingBehavior()
{
}

void EntityPacingBehavior::initializePositions()
{
}

void EntityPacingBehavior::onLoad()
{
	this->anchorPosition = GameUtils::getWorldCoords(this->entity);

	this->entity->watchForAttachedBehavior<EntityMovementCollisionBehavior>([=](EntityMovementCollisionBehavior* collisionBehavior)
	{
		collisionBehavior->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
		{
			this->cancelPacing();
			
			return CollisionObject::CollisionResult::DoNothing;
		});

		collisionBehavior->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
		{	
			this->cancelPacing();

			return CollisionObject::CollisionResult::DoNothing;
		});
	});

	this->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(2.0f, 7.5f)),
		CallFunc::create([=]()
		{
			this->assignDestination();
		}),
		nullptr
	));
}

void EntityPacingBehavior::assignDestination()
{
	float newDelta = 0.0f;

	do
	{
		newDelta = RandomHelper::random_real(-EntityPacingBehavior::TravelDistanceMax, EntityPacingBehavior::TravelDistanceMax);
	}
	while (std::abs(newDelta - this->destinationDelta) < EntityPacingBehavior::TravelDistanceMin);

	this->destinationDelta = newDelta;

	float destinationX = this->anchorPosition.x + this->destinationDelta;

	// Leverage the cinematic movement code for enemy pacing, should work fine
	this->entity->setState(StateKeys::PatrolDestinationX, Value(destinationX));

	this->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(2.0f, 7.5f)),
		CallFunc::create([=]()
		{
			this->assignDestination();
		}),
		nullptr
	));
}

void EntityPacingBehavior::cancelPacing()
{
	this->entity->clearState(StateKeys::PatrolDestinationX);
}
