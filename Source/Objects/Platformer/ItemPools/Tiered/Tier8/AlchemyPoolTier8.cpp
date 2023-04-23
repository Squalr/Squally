#include "AlchemyPoolTier8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier8* AlchemyPoolTier8::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier8* instance = new AlchemyPoolTier8(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier8::AlchemyPoolTier8(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t8", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(VoidFlower::create(), ItemChance::Probability::VeryCommon));

	// Phasing out
	// this->addItemToPool(ItemChance::create(FrostBerries::create(), ItemChance::Probability::Uncommon)); // Excluded for lore
	// this->addItemToPool(ItemChance::create(Snowball::create(), ItemChance::Probability::Uncommon)); // Excluded for lore

	// Bomb
	this->addItemToPool(ItemChance::create(Meteorite::create(), ItemChance::Probability::Common));
}

AlchemyPoolTier8::~AlchemyPoolTier8()
{
}
