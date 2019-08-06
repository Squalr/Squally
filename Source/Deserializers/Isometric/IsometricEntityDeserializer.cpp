#include "IsometricEntityDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Isometric/IsometricEntities.h"

using namespace cocos2d;

const std::string IsometricEntityDeserializer::MapKeyTypeEntity = "entity";

IsometricEntityDeserializer* IsometricEntityDeserializer::create()
{
	IsometricEntityDeserializer* instance = new IsometricEntityDeserializer();

	instance->autorelease();

	return instance;
}

IsometricEntityDeserializer::IsometricEntityDeserializer() : super(IsometricEntityDeserializer::MapKeyTypeEntity)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	this->deserializers[IsometricSqually::MapKeySqually] = [=](ValueMap properties) { return (GameObject*)IsometricSqually::deserialize(properties); };
	this->deserializers[IsometricBall::MapKeyBall] = [=](ValueMap properties) { return (GameObject*)IsometricBall::deserialize(properties); };
	this->deserializers[Shiftman::MapKeyShiftman] = [=](ValueMap properties) { return (GameObject*)Shiftman::deserialize(properties); };
}

IsometricEntityDeserializer::~IsometricEntityDeserializer()
{
}
