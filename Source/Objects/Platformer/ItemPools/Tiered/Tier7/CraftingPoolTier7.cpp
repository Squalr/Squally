#include "CraftingPoolTier7.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

CraftingPoolTier7* CraftingPoolTier7::create(SampleMethod sampleMethod, int min, int max)
{
	CraftingPoolTier7* instance = new CraftingPoolTier7(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

CraftingPoolTier7::CraftingPoolTier7(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "crafting-pool-t7", sampleMethod, min, max)
{
	// Gems
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Obsidian::create(), ItemChance::Probability::Rare));

	// Gems (phasing out)
	// this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Legendary));
	// this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Legendary));
	// this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Sulfur::create(), ItemChance::Probability::Rare));

	// Metals
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Uncommon));

	// Materials
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Common));
}

CraftingPoolTier7::~CraftingPoolTier7()
{
}
