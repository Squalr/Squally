#include "CraftingPoolTier2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

CraftingPoolTier2* CraftingPoolTier2::create(SampleMethod sampleMethod, int min, int max)
{
	CraftingPoolTier2* instance = new CraftingPoolTier2(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

CraftingPoolTier2::CraftingPoolTier2(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "crafting-pool-t2", sampleMethod, min, max)
{
	// Gems
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Legendary));

	// Gems (phasing out)
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Rare));

	// Metals
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Silver::create(), ItemChance::Probability::Epic));

	// Materials
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Dirt::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Stone::create(), ItemChance::Probability::Common));
}

CraftingPoolTier2::~CraftingPoolTier2()
{
}
