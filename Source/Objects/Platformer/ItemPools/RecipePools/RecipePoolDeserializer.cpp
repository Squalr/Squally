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

	// Endian forest pocket pools
	this->deserializers[AlchemyPoolEF::PoolName] = [=](ValueMap properties) { return (GameObject*)AlchemyPoolEF::create(properties); };
	this->deserializers[SmithingPoolEF::PoolName] = [=](ValueMap properties) { return (GameObject*)SmithingPoolEF::create(properties); };
}

RecipePoolDeserializer::~RecipePoolDeserializer()
{
}
