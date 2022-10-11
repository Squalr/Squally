#include "PotionPoolTier7.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier7* PotionPoolTier7::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier7* instance = new PotionPoolTier7(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier7::PotionPoolTier7(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t7", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier7::~PotionPoolTier7()
{
}
