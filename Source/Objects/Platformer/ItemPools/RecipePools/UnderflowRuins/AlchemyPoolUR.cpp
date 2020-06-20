#include "AlchemyPoolUR.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string AlchemyPoolUR::PoolName = "alchemy-pool-ur";

AlchemyPoolUR* AlchemyPoolUR::create(ValueMap& properties)
{
	AlchemyPoolUR* instance = new AlchemyPoolUR(properties);

	instance->autorelease();

	return instance;
}

AlchemyPoolUR::AlchemyPoolUR(ValueMap& properties) : super(properties, AlchemyPoolUR::PoolName, SampleMethod::Unbounded, 1, 1)
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
	this->addItemToPool(ItemChance::create(TransmuteCopperToIron::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(TransmuteQuartzToEmerald::create(), ItemChance::Probability::Guaranteed));
}

AlchemyPoolUR::~AlchemyPoolUR()
{
}
