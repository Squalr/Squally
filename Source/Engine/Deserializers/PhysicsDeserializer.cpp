#include "PhysicsDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Physics/PhysicsLayer.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string PhysicsDeserializer::MapKeyPhysicsLayer = "physics";

PhysicsDeserializer* PhysicsDeserializer::create()
{
	PhysicsDeserializer* instance = new PhysicsDeserializer();

	instance->autorelease();

	return instance;
}

PhysicsDeserializer::PhysicsDeserializer() : super(PhysicsDeserializer::MapKeyPhysicsLayer)
{
}

PhysicsDeserializer::~PhysicsDeserializer()
{
}

void PhysicsDeserializer::deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args)
{
	std::string name = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyName, Value("")).asString();

	args->handle();

	ValueMap properties = args->properties;

	args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(PhysicsLayer::create(properties, name), args->layerIndex));
}
