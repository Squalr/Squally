#include "DropPoolURGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/UnderflowRuins/CurrencyPoolURGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/AlchemyPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/SmithingPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolURGeneric::PoolName = "ur-generic";

DropPoolURGeneric* DropPoolURGeneric::create(ValueMap& properties)
{
	DropPoolURGeneric* instance = new DropPoolURGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolURGeneric::DropPoolURGeneric(ValueMap& properties) : super(properties, DropPoolURGeneric::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolURGeneric::create(properties),
	{
		CardPoolTier1::create(SampleMethod::Random, 0, 1),
		AlchemyPoolTier1::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier1::create(SampleMethod::Random, 1, 2),
		PotionPoolTier1::create(SampleMethod::Random, 0, 1)
	})
{
}

DropPoolURGeneric::~DropPoolURGeneric()
{
}
