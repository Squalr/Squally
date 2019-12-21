#include "PhysicsDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Physics/PhysicsInitializer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string PhysicsDeserializer::MapKeyPhysics = "physics";

PhysicsDeserializer* PhysicsDeserializer::create()
{
	PhysicsDeserializer* instance = new PhysicsDeserializer();

	instance->autorelease();

	return instance;
}

PhysicsDeserializer::PhysicsDeserializer() : super()
{
}

PhysicsDeserializer::~PhysicsDeserializer()
{
}

void PhysicsDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	PhysicsInitializer* PhysicsInitializer = PhysicsInitializer::create(properties);

	owner->addChild(PhysicsInitializer);
}
