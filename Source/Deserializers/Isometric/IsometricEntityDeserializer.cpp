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

void IsometricEntityDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	const std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyName, Value("")).asString();

	if (this->deserializers.find(name) != this->deserializers.end())
	{
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(this->deserializers[name](properties)));
	}
	else
	{
		CCLOG("Unknown entity encountered: %s", name.c_str());
	}
}
