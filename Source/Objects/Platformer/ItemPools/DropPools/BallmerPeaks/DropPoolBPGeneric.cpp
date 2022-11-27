#include "DropPoolBPGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/BallmerPeaks/CurrencyPoolBPGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/AlchemyPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/CardPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/SmithingPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/PotionPoolTier7.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolBPGeneric::PoolName = "bp-generic";

DropPoolBPGeneric* DropPoolBPGeneric::create(ValueMap& properties)
{
	DropPoolBPGeneric* instance = new DropPoolBPGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolBPGeneric::DropPoolBPGeneric(ValueMap& properties) : super(properties, DropPoolBPGeneric::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolBPGeneric::create(properties),
	{
		CardPoolTier7::create(SampleMethod::Random, 0, 1),
		AlchemyPoolTier7::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier7::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier7::create(SampleMethod::Random, 0, 1),
	})
{
}

DropPoolBPGeneric::~DropPoolBPGeneric()
{
}
