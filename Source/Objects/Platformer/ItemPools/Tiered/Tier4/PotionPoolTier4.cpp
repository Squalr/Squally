#include "PotionPoolTier4.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier4* PotionPoolTier4::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier4* instance = new PotionPoolTier4(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier4::PotionPoolTier4(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t4", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier4::~PotionPoolTier4()
{
}
