#include "Water.h"

#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Water::MapKeyWater = "water";
const float Water::WaterGravity = 0.0f;

Water* Water::create(ValueMap& initProperties)
{
	Water* instance = new Water(initProperties);

	instance->autorelease();

	return instance;
}

Water::Water(ValueMap& initProperties) : super(initProperties)
{
	Size waterSize = Size(this->properties.at(SerializableObject::MapKeyWidth).asFloat(), this->properties.at(SerializableObject::MapKeyHeight).asFloat());
	
	this->waterCollision = CollisionObject::create(PhysicsBody::createBox(waterSize), (CollisionType)PlatformerCollisionType::Water, false, false);

	this->addChild(this->waterCollision);
}

Water::~Water()
{
}

void Water::onEnter()
{
	super::onEnter();
}

void Water::initializePositions()
{
	super::initializePositions();
}

void Water::initializeListeners()
{
	super::initializeListeners();

	this->waterCollision->setContactUpdateCallback(CC_CALLBACK_2(Water::applyWaterForce, this));

	this->waterCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// Speed is applied in the update applyWaterForce

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Water::applyWaterForce(std::set<CollisionObject*>* targets, float dt)
{
	for (auto it = targets->begin(); it != targets->end(); it++)
	{
		(*it)->setVelocity((*it)->getVelocity() + Vec2(0.0f, Water::WaterGravity * dt));
	}
}
