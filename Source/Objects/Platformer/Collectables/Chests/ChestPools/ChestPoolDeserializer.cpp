#include "ChestPoolDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Objects/Platformer/Collectables/Chests/ChestPools/ChestPools.h"

using namespace cocos2d;

const std::string ChestPoolDeserializer::MapKeyTypeChestPool = "chest-pool";

ChestPoolDeserializer* ChestPoolDeserializer::create()
{
	ChestPoolDeserializer* instance = new ChestPoolDeserializer();

	instance->autorelease();

	return instance;
}

ChestPoolDeserializer::ChestPoolDeserializer() : super(ChestPoolDeserializer::MapKeyTypeChestPool)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	// Endian forest chest pools
	this->deserializers[ChestPoolEFGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFGeneric::create(properties); };
}

ChestPoolDeserializer::~ChestPoolDeserializer()
{
}
