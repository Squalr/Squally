#include "EntityPacingBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string EntityPacingBehavior::MapKeyAttachedBehavior = "pacing";
const float EntityPacingBehavior::TravelDistanceMax = 512.0f;

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

	this->assignDestination();
}

void EntityPacingBehavior::assignDestination()
{
	float destinationDelta = RandomHelper::random_real(-EntityPacingBehavior::TravelDistanceMax, EntityPacingBehavior::TravelDistanceMax);

	float destinationX = this->anchorPosition.x + destinationDelta;

	// Leverage the cinematic movement code for enemy pacing, should work fine
	this->entity->setState(StateKeys::CinematicDestinationX, Value(destinationX));

	this->runAction(Sequence::create(
		DelayTime::create(RandomHelper::random_real(2.5f, 7.5f)),
		CallFunc::create([=]()
		{
			this->assignDestination();
		}),
		nullptr
	));
}
