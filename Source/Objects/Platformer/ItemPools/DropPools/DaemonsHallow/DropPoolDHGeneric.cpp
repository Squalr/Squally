#include "DropPoolDHGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/DaemonsHallow/CurrencyPoolDHGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/CardPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolDHGeneric::PoolName = "dh-generic";

DropPoolDHGeneric* DropPoolDHGeneric::create(ValueMap& properties)
{
	DropPoolDHGeneric* instance = new DropPoolDHGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolDHGeneric::DropPoolDHGeneric(ValueMap& properties) : super(properties, DropPoolDHGeneric::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolDHGeneric::create(properties),
	{
		CardPoolTier6::create(SampleMethod::Random, 0, 1),
		AlchemyPoolTier6::create(SampleMethod::Random, 1, 2),
		SmithingPoolTier6::create(SampleMethod::Random, 1, 2),
		// PotionPoolTier6::create(SampleMethod::Random, 0, 1),
	})
{
}

DropPoolDHGeneric::~DropPoolDHGeneric()
{
}
