#include "ChestPoolDMCoal.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDMCoal::PoolName = "dm-coal";

ChestPoolDMCoal* ChestPoolDMCoal::create(ValueMap& properties)
{
	ChestPoolDMCoal* instance = new ChestPoolDMCoal(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDMCoal::ChestPoolDMCoal(ValueMap& properties) : super(
	properties, ChestPoolDMCoal::PoolName, SampleMethod::Random, 1, 3,
	{
	})
{
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolDMCoal::~ChestPoolDMCoal()
{
}
