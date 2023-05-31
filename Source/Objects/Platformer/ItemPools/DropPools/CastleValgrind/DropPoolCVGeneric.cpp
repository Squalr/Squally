#include "DropPoolCVGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/CastleValgrind/CurrencyPoolCVGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/AlchemyPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/SmithingPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/PotionPoolTier4.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolCVGeneric::PoolName = "cv-generic";

DropPoolCVGeneric* DropPoolCVGeneric::create(ValueMap& properties)
{
	DropPoolCVGeneric* instance = new DropPoolCVGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolCVGeneric::DropPoolCVGeneric(ValueMap& properties) : super(properties, DropPoolCVGeneric::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolCVGeneric::create(properties),
	{
		AlchemyPoolTier4::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier4::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier4::create(SampleMethod::Random, 0, 1),
	})
{
}

DropPoolCVGeneric::~DropPoolCVGeneric()
{
}
