#include "ChestPoolDMGold.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDMGold::PoolName = "dm-gold";

ChestPoolDMGold* ChestPoolDMGold::create(ValueMap& properties)
{
	ChestPoolDMGold* instance = new ChestPoolDMGold(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDMGold::ChestPoolDMGold(ValueMap& properties) : super(
	properties, ChestPoolDMGold::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolDMGold::~ChestPoolDMGold()
{
}
