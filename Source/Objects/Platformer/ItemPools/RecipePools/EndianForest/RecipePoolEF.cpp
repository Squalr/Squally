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
	this->addItemToPool(ItemChance::create(IronSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(RapierPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenMalletPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SpikedClubPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenWandPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(EnchantedWandPlans::create(), ItemChance::Probability::Guaranteed));
}

RecipePoolEF::~RecipePoolEF()
{
}
