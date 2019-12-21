#include "PotionPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier1* PotionPoolTier1::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier1* instance = new PotionPoolTier1(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier1::PotionPoolTier1(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t1", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier1::~PotionPoolTier1()
{
}
