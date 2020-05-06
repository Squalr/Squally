#include "PotionPoolTier2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PotionPoolTier2* PotionPoolTier2::create(SampleMethod sampleMethod, int min, int max)
{
	PotionPoolTier2* instance = new PotionPoolTier2(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

PotionPoolTier2::PotionPoolTier2(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "potion-pool-t2", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

PotionPoolTier2::~PotionPoolTier2()
{
}
