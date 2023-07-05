#include "AlchemyPoolFF.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string AlchemyPoolFF::PoolName = "alchemy-pool-ff";

AlchemyPoolFF* AlchemyPoolFF::create(ValueMap& properties)
{
	AlchemyPoolFF* instance = new AlchemyPoolFF(properties);

	instance->autorelease();

	return instance;
}

AlchemyPoolFF::AlchemyPoolFF(ValueMap& properties) : super(properties, AlchemyPoolFF::PoolName, SampleMethod::Unbounded, 1, 1)
{
	// Allows for stability in item ordering
	this->toggleDisableShuffle(true);
	
	this->addItemToPool(ItemChance::create(BarbedHelmPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SnailShellSpikedPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WizardsHatShadowPlans::create(), ItemChance::Probability::Guaranteed));

	// Potions
	this->addItemToPool(ItemChance::create(SuperiorHealthFlaskRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GreaterHealthPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(HealthPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(IncrementHealthFlaskRecipe::create(), ItemChance::Probability::Guaranteed));

	this->addItemToPool(ItemChance::create(SuperiorManaFlaskRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GreaterManaPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(ManaPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(IncrementManaFlaskRecipe::create(), ItemChance::Probability::Guaranteed));

	// Potions
	this->addItemToPool(ItemChance::create(SuperiorHealthFlaskRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GreaterHealthPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(HealthPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(IncrementHealthFlaskRecipe::create(), ItemChance::Probability::Guaranteed));

	this->addItemToPool(ItemChance::create(SuperiorManaFlaskRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GreaterManaPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(ManaPotionRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(IncrementManaFlaskRecipe::create(), ItemChance::Probability::Guaranteed));

	// Special
	this->addItemToPool(ItemChance::create(HeliumBombRecipe::create(), ItemChance::Probability::Guaranteed));

	// Bombs
	this->addItemToPool(ItemChance::create(FragGrenadeRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SpikedBombRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(PepperBombRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(LargeBombRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SteelBombRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SmallBombRecipe::create(), ItemChance::Probability::Guaranteed));
	
	// Transmutes
	this->addItemToPool(ItemChance::create(TransmuteWoodToCoalRecipe::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(TransmuteCopperToQuartzRecipe::create(), ItemChance::Probability::Guaranteed));
}

AlchemyPoolFF::~AlchemyPoolFF()
{
}
