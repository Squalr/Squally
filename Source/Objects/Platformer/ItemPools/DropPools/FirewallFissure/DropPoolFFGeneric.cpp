#include "DropPoolFFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/FirewallFissure/CurrencyPoolFFGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolFFGeneric::PoolName = "ff-generic";

DropPoolFFGeneric* DropPoolFFGeneric::create(ValueMap& properties)
{
	DropPoolFFGeneric* instance = new DropPoolFFGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolFFGeneric::DropPoolFFGeneric(ValueMap& properties) : super(properties, DropPoolFFGeneric::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolFFGeneric::create(properties),
	{
		AlchemyPoolTier6::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier6::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier6::create(SampleMethod::Random, 0, 1),
	})
{
}

DropPoolFFGeneric::~DropPoolFFGeneric()
{
}
