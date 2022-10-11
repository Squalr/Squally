#include "DropPoolDMGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/DataMines/CurrencyPoolDMGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolDMGeneric::PoolName = "dm-generic";

DropPoolDMGeneric* DropPoolDMGeneric::create(ValueMap& properties)
{
	DropPoolDMGeneric* instance = new DropPoolDMGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolDMGeneric::DropPoolDMGeneric(ValueMap& properties) : super(properties, DropPoolDMGeneric::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolDMGeneric::create(properties),
	{
		CardPoolTier3::create(SampleMethod::Random, 0, 1),
		AlchemyPoolTier3::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier3::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier3::create(SampleMethod::Random, 0, 1),
	})
{
}

DropPoolDMGeneric::~DropPoolDMGeneric()
{
}
