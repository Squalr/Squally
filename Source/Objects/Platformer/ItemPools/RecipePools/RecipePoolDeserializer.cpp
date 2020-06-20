#include "RecipePoolDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePools.h"

using namespace cocos2d;

const std::string RecipePoolDeserializer::MapKeyTypeRecipePool = "recipe-pool";

RecipePoolDeserializer* RecipePoolDeserializer::create()
{
	RecipePoolDeserializer* instance = new RecipePoolDeserializer();

	instance->autorelease();

	return instance;
}

RecipePoolDeserializer::RecipePoolDeserializer() : super(RecipePoolDeserializer::MapKeyTypeRecipePool)
{
	this->deserializers = std::map<std::string, std::function<GameObject*(ValueMap)>>();

	// EF
	this->deserializers[AlchemyPoolEF::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolEF::create(properties); };
	this->deserializers[SmithingPoolEF::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolEF::create(properties); };

	// UR
	this->deserializers[AlchemyPoolUR::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolUR::create(properties); };
	this->deserializers[SmithingPoolUR::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolUR::create(properties); };

	// DM
	this->deserializers[AlchemyPoolDM::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolDM::create(properties); };
	this->deserializers[SmithingPoolDM::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolDM::create(properties); };

	// CV
	this->deserializers[AlchemyPoolCV::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolCV::create(properties); };
	this->deserializers[SmithingPoolCV::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolCV::create(properties); };

	// BP
	this->deserializers[AlchemyPoolBP::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolBP::create(properties); };
	this->deserializers[SmithingPoolBP::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolBP::create(properties); };

	// DH
	this->deserializers[AlchemyPoolDH::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolDH::create(properties); };
	this->deserializers[SmithingPoolDH::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolDH::create(properties); };

	// LC
	this->deserializers[AlchemyPoolLC::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolLC::create(properties); };
	this->deserializers[SmithingPoolLC::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolLC::create(properties); };

	// VS
	this->deserializers[AlchemyPoolVS::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolVS::create(properties); };
	this->deserializers[SmithingPoolVS::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolVS::create(properties); };
}

RecipePoolDeserializer::~RecipePoolDeserializer()
{
}
