#include "ChestPoolDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Objects/Platformer/ItemPools/ChestPools/ChestPools.h"

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

	// EF pools
	this->deserializers[ChestPoolEFGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFGeneric::create(properties); };
	this->deserializers[ChestPoolRamWheel::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolRamWheel::create(properties); };
	this->deserializers[ChestPoolSpecialAra::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolSpecialAra::create(properties); };

	// UR pools
	this->deserializers[ChestPoolBlueGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolBlueGem::create(properties); };
	this->deserializers[ChestPoolPurpleGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolPurpleGem::create(properties); };
	this->deserializers[ChestPoolRedGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolRedGem::create(properties); };
}

ChestPoolDeserializer::~ChestPoolDeserializer()
{
}
