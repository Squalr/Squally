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

	// Special
	this->deserializers[ChestPoolDisplayOr::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDisplayOr::create(properties); };

	// EF pools
	this->deserializers[ChestPoolEFDungeonMap::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFDungeonMap::create(properties); };
	this->deserializers[ChestPoolEFEquipment::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFEquipment::create(properties); };
	this->deserializers[ChestPoolEFGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFGeneric::create(properties); };
	this->deserializers[ChestPoolEFRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFRare::create(properties); };
	this->deserializers[ChestPoolEFWeapon::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolEFWeapon::create(properties); };
	this->deserializers[ChestPoolRamWheel::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolRamWheel::create(properties); };

	// UR pools
	this->deserializers[ChestPoolURGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolURGeneric::create(properties); };
	this->deserializers[ChestPoolURMirror::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolURMirror::create(properties); };
	this->deserializers[ChestPoolURRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolURRare::create(properties); };

	// DM pools
	this->deserializers[ChestPoolDMCoal::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDMCoal::create(properties); };
	this->deserializers[ChestPoolDMDiamond::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDMDiamond::create(properties); };
	this->deserializers[ChestPoolDMGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDMGeneric::create(properties); };
	this->deserializers[ChestPoolDMGold::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDMGold::create(properties); };
	this->deserializers[ChestPoolDMRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDMRare::create(properties); };

	// CV pools
	this->deserializers[ChestPoolCVGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolCVGeneric::create(properties); };
	this->deserializers[ChestPoolCVRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolCVRare::create(properties); };

	// LC pools
	this->deserializers[ChestPoolBlueGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolBlueGem::create(properties); };
	this->deserializers[ChestPoolPurpleGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolPurpleGem::create(properties); };
	this->deserializers[ChestPoolRedGem::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolRedGem::create(properties); };
	this->deserializers[ChestPoolLCGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolLCGeneric::create(properties); };
	this->deserializers[ChestPoolLCRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolLCRare::create(properties); };

	// DH pools
	this->deserializers[ChestPoolDHGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDHGeneric::create(properties); };
	this->deserializers[ChestPoolDHRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolDHRare::create(properties); };

	// BP pools
	this->deserializers[ChestPoolBPGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolBPGeneric::create(properties); };
	this->deserializers[ChestPoolBPRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolBPRare::create(properties); };

	// VS pools
	this->deserializers[ChestPoolVSGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolVSGeneric::create(properties); };
	this->deserializers[ChestPoolVSRare::PoolName] = [=](ValueMap properties) { return (GameObject*)ChestPoolVSRare::create(properties); };
}

ChestPoolDeserializer::~ChestPoolDeserializer()
{
}
