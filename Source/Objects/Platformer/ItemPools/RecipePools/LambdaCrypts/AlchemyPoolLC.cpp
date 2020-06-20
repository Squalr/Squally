#include "AlchemyPoolLC.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string AlchemyPoolLC::PoolName = "alchemy-pool-lc";

AlchemyPoolLC* AlchemyPoolLC::create(ValueMap& properties)
{
	AlchemyPoolLC* instance = new AlchemyPoolLC(properties);

	instance->autorelease();

	return instance;
}

AlchemyPoolLC::AlchemyPoolLC(ValueMap& properties) : super(properties, AlchemyPoolLC::PoolName, SampleMethod::Unbounded, 1, 1)
{
	// Allows for stability in item ordering
	this->toggleDisableShuffle(true);

	// Potions
	this->addItemToPool(ItemChance::create(IncrementHealthFlaskRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(HealthPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(ManaPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	
	// Transmutes
	this->addItemToPool(ItemChance::create(TransmuteWoodToCoalRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(TransmuteCopperToQuartzRecipe::create(), ItemChance::Probability::Guaranteed));
}

AlchemyPoolLC::~AlchemyPoolLC()
{
}
