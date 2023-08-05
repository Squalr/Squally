#include "DropPoolVSGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/VoidStar/CurrencyPoolVSGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/AlchemyPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/SmithingPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/PotionPoolTier8.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolVSGeneric::PoolName = "vs-generic";

DropPoolVSGeneric* DropPoolVSGeneric::create(ValueMap& properties)
{
	DropPoolVSGeneric* instance = new DropPoolVSGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolVSGeneric::DropPoolVSGeneric(ValueMap& properties) : super(properties, DropPoolVSGeneric::PoolName, SampleMethod::Random, 1, 3, CurrencyPoolVSGeneric::create(properties),
	{
		AlchemyPoolTier8::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier8::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier8::create(SampleMethod::Random, 0, 1),
	})
{
}

DropPoolVSGeneric::~DropPoolVSGeneric()
{
}
