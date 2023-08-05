#include "DropPoolLCGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/LambdaCrypts/CurrencyPoolLCGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolLCGeneric::PoolName = "lc-generic";

DropPoolLCGeneric* DropPoolLCGeneric::create(ValueMap& properties)
{
	DropPoolLCGeneric* instance = new DropPoolLCGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolLCGeneric::DropPoolLCGeneric(ValueMap& properties) : super(properties, DropPoolLCGeneric::PoolName, SampleMethod::Random, 1, 3, CurrencyPoolLCGeneric::create(properties),
	{
		AlchemyPoolTier5::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier5::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier5::create(SampleMethod::Random, 0, 1),
	})
{
}

DropPoolLCGeneric::~DropPoolLCGeneric()
{
}
