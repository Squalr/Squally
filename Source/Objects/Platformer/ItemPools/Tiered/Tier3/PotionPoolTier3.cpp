#include "PotionPoolTier3.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier3* PotionPoolTier3::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier3* instance = new PotionPoolTier3(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier3::PotionPoolTier3(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t3", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier3::~PotionPoolTier3()
{
}
