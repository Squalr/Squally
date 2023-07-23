#include "ChestPoolCVRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/AlchemyPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/SmithingPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/PotionPoolTier4.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolCVRare::PoolName = "cv-rare";

ChestPoolCVRare* ChestPoolCVRare::create(ValueMap& properties)
{
	ChestPoolCVRare* instance = new ChestPoolCVRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolCVRare::ChestPoolCVRare(ValueMap& properties) : super(
	properties, ChestPoolCVRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier4::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier4::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolCVRare::~ChestPoolCVRare()
{
}
