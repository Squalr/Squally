#include "PotionPoolTier8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier8* PotionPoolTier8::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier8* instance = new PotionPoolTier8(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier8::PotionPoolTier8(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t8", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier8::~PotionPoolTier8()
{
}
