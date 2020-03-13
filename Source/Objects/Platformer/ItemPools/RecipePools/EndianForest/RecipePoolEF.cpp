#include "RecipePoolEF.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string RecipePoolEF::PoolName = "recipe-pool-ef";

RecipePoolEF* RecipePoolEF::create(ValueMap& properties)
{
	RecipePoolEF* instance = new RecipePoolEF(properties);

	instance->autorelease();

	return instance;
}

RecipePoolEF::RecipePoolEF(ValueMap& properties) : super(properties, RecipePoolEF::PoolName, SampleMethod::Unbounded, 1, 1)
{
	this->addItemToPool(ItemChance::create(BattleAxePlans::create(), ItemChance::Probability::Guaranteed));
}

RecipePoolEF::~RecipePoolEF()
{
}
