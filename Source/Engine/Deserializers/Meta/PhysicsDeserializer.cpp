#include "PhysicsDeserializer.h"

#include "cocos/base/CCValue.h"

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
	float gravity = GameUtils::getKeyOrDefault(properties, PhysicsDeserializer::MapKeyPhysics, Value(0.0f)).asFloat();
}

/*
void PhysicsDeserializer::deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args)
{
}
*/
