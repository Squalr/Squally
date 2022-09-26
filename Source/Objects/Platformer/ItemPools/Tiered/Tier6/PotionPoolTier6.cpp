#include "PotionPoolTier6.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier6* PotionPoolTier6::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier6* instance = new PotionPoolTier6(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier6::PotionPoolTier6(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t6", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier6::~PotionPoolTier6()
{
}
