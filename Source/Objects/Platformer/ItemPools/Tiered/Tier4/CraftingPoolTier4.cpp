#include "CraftingPoolTier4.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

CraftingPoolTier4* CraftingPoolTier4::create(SampleMethod sampleMethod, int min, int max)
{
	CraftingPoolTier4* instance = new CraftingPoolTier4(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

CraftingPoolTier4::CraftingPoolTier4(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "crafting-pool-t4", sampleMethod, min, max)
{
	// Gems
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Jade::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Sulfur::create(), ItemChance::Probability::Legendary));

	// Gems (phasing out)
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Rare));

	// Metals
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Silver::create(), ItemChance::Probability::Epic));

	// Materials
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Dirt::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Stone::create(), ItemChance::Probability::Common));
}

CraftingPoolTier4::~CraftingPoolTier4()
{
}
