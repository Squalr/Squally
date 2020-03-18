#include "CraftingPoolTier3.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

CraftingPoolTier3* CraftingPoolTier3::create(SampleMethod sampleMethod, int min, int max)
{
	CraftingPoolTier3* instance = new CraftingPoolTier3(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

CraftingPoolTier3::CraftingPoolTier3(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "crafting-pool-t3", sampleMethod, min, max)
{
	// Gems
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Legendary));

	// Gems (phasing out)
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Rare));

	// Metals
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Tin::create(), ItemChance::Probability::Epic));

	// Materials
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Common));
}

CraftingPoolTier3::~CraftingPoolTier3()
{
}
