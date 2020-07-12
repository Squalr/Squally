#include "ChestPoolDMDiamond.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDMDiamond::PoolName = "dm-diamond";

ChestPoolDMDiamond* ChestPoolDMDiamond::create(ValueMap& properties)
{
	ChestPoolDMDiamond* instance = new ChestPoolDMDiamond(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDMDiamond::ChestPoolDMDiamond(ValueMap& properties) : super(
	properties, ChestPoolDMDiamond::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::VeryCommon));
}

ChestPoolDMDiamond::~ChestPoolDMDiamond()
{
}
