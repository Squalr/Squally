#include "AlchemyPoolDM.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string AlchemyPoolDM::PoolName = "alchemy-pool-dm";

AlchemyPoolDM* AlchemyPoolDM::create(ValueMap& properties)
{
	AlchemyPoolDM* instance = new AlchemyPoolDM(properties);

	instance->autorelease();

	return instance;
}

AlchemyPoolDM::AlchemyPoolDM(ValueMap& properties) : super(properties, AlchemyPoolDM::PoolName, SampleMethod::Unbounded, 1, 1)
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

AlchemyPoolDM::~AlchemyPoolDM()
{
}
