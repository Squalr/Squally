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
	
	// Testing
	this->deserializers[ChestPoolPinata::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolPinata::create(properties); };

	// EF pools
	this->deserializers[ChestPoolEFEquipment::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFEquipment::create(properties); };
	this->deserializers[ChestPoolEFGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFGeneric::create(properties); };
	this->deserializers[ChestPoolEFRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFRare::create(properties); };
	this->deserializers[ChestPoolEFWeapon::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFWeapon::create(properties); };
	this->deserializers[ChestPoolRamWheel::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolRamWheel::create(properties); };

	// UR pools
	this->deserializers[ChestPoolBlueGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolBlueGem::create(properties); };
	this->deserializers[ChestPoolPurpleGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolPurpleGem::create(properties); };
	this->deserializers[ChestPoolRedGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolRedGem::create(properties); };
	this->deserializers[ChestPoolUREquipment::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolUREquipment::create(properties); };
	this->deserializers[ChestPoolURGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolURGeneric::create(properties); };
	this->deserializers[ChestPoolURRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolURRare::create(properties); };
}

ChestPoolDeserializer::~ChestPoolDeserializer()
{
}
