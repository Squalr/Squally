#include "AlchemyPoolEF.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string AlchemyPoolEF::PoolName = "alchemy-pool-ef";

AlchemyPoolEF* AlchemyPoolEF::create(ValueMap& properties)
{
	AlchemyPoolEF* instance = new AlchemyPoolEF(properties);

	instance->autorelease();

	return instance;
}

AlchemyPoolEF::AlchemyPoolEF(ValueMap& properties) : super(properties, AlchemyPoolEF::PoolName, SampleMethod::Unbounded, 1, 1)
{
	// Potions
	this->addItemToPool(ItemChance::create(IncrementHealthFlaskRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(HealthPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(ManaPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	
	// Transmutes
	this->addItemToPool(ItemChance::create(TransmuteWoodToCoalRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(TransmuteCopperToQuartzRecipe::create(), ItemChance::Probability::Guaranteed));
}

AlchemyPoolEF::~AlchemyPoolEF()
{
}
