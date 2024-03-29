#include "DropPoolDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Objects/Platformer/ItemPools/DropPools/DropPools.h"

using namespace cocos2d;

const std::string DropPoolDeserializer::MapKeyTypeDropPool = "drop-pool";

DropPoolDeserializer* DropPoolDeserializer::create()
{
	DropPoolDeserializer* instance = new DropPoolDeserializer();

	instance->autorelease();

	return instance;
}

DropPoolDeserializer::DropPoolDeserializer() : super(DropPoolDeserializer::MapKeyTypeDropPool)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();
	
	this->deserializers[EmptyDropPool::PoolName] = [=](ValueMap properties) { return (GameObject*)EmptyDropPool::create(properties); };
	this->deserializers[ErrorDropPool::PoolName] = [=](ValueMap properties) { return (GameObject*)ErrorDropPool::create(properties); };

	// EF
	this->deserializers[DropPoolEFGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolEFGeneric::create(properties); };
	this->deserializers[DropPoolEFGorgon::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolEFGorgon::create(properties); };
	this->deserializers[DropPoolEFGrogg::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolEFGrogg::create(properties); };
	this->deserializers[DropPoolEFWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolEFWeak::create(properties); };

	// UR
	this->deserializers[DropPoolURGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolURGeneric::create(properties); };
	this->deserializers[DropPoolUROsiris::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolUROsiris::create(properties); };
	this->deserializers[DropPoolURWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolURWeak::create(properties); };

	// DM
	this->deserializers[DropPoolDMGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolDMGeneric::create(properties); };
	this->deserializers[DropPoolDMWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolDMWeak::create(properties); };

	// CV
	this->deserializers[DropPoolCVAgnes::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolCVAgnes::create(properties); };
	this->deserializers[DropPoolCVGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolCVGeneric::create(properties); };
	this->deserializers[DropPoolCVWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolCVWeak::create(properties); };

	// LC
	this->deserializers[DropPoolLCGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolLCGeneric::create(properties); };
	this->deserializers[DropPoolLCElric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolLCElric::create(properties); };
	this->deserializers[DropPoolLCKingZul::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolLCKingZul::create(properties); };
	this->deserializers[DropPoolLCLazarus::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolLCLazarus::create(properties); };
	this->deserializers[DropPoolLCWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolLCWeak::create(properties); };

	// FF
	this->deserializers[DropPoolFFGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolFFGeneric::create(properties); };
	this->deserializers[DropPoolFFWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolFFWeak::create(properties); };

	// BP
	this->deserializers[DropPoolBPGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolBPGeneric::create(properties); };
	this->deserializers[DropPoolBPWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolBPWeak::create(properties); };

	// VS
	this->deserializers[DropPoolVSGeneric::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolVSGeneric::create(properties); };
	this->deserializers[DropPoolVSWeak::PoolName] = [=](ValueMap properties) { return (GameObject*)DropPoolVSWeak::create(properties); };
}

DropPoolDeserializer::~DropPoolDeserializer()
{
}
