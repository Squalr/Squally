#include "PotionPoolTier5.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier5* PotionPoolTier5::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier5* instance = new PotionPoolTier5(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier5::PotionPoolTier5(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t5", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier5::~PotionPoolTier5()
{
}
