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

const std::string EntityPacingBehavior::MapKey = "pacing";
const std::string EntityPacingBehavior::PropertyTravelDistance = "travel-distance";
const float EntityPacingBehavior::DefaultTravelDistanceMax = 512.0f;
const float EntityPacingBehavior::DefaultTravelDistanceMin = 96.0f;

EntityPacingBehavior* EntityPacingBehavior::create(GameObject* owner)
{
	EntityPacingBehavior* instance = new EntityPacingBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityPacingBehavior::EntityPacingBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->travelDistance = EntityPacingBehavior::DefaultTravelDistanceMax;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->travelDistance = this->entity->getPropertyOrDefault(EntityPacingBehavior::PropertyTravelDistance, Value(EntityPacingBehavior::DefaultTravelDistanceMax)).asFloat();
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
		collisionBehavior->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
		{
			this->cancelPacing();
			
			return CollisionObject::CollisionResult::DoNothing;
		});

		collisionBehavior->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
		{	
			this->cancelPacing();

			return CollisionObject::CollisionResult::DoNothing;
		});
	});

	this->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(0.5f, 4.0f)),
		CallFunc::create([=]()
		{
			this->assignDestination();
		}),
		nullptr
	));
}

void EntityPacingBehavior::onDisable()
{
	super::onDisable();
}

void EntityPacingBehavior::assignDestination()
{
	const int LoopsMax = 32;
	float newDelta = 0.0f;
	int loopSafety = 0;

	do
	{
		newDelta = RandomHelper::random_real(-this->travelDistance, this->travelDistance);

		if (loopSafety++ > LoopsMax)
		{
			break;
		}
	}
	while (std::abs(newDelta - this->destinationDelta) < EntityPacingBehavior::DefaultTravelDistanceMin);

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
