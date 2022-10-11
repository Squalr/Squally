#include "DropPoolDMWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/DataMines/CurrencyPoolDMGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolDMWeak::PoolName = "dm-weak";

DropPoolDMWeak* DropPoolDMWeak::create(ValueMap& properties)
{
	DropPoolDMWeak* instance = new DropPoolDMWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolDMWeak::DropPoolDMWeak(ValueMap& properties) : super(properties, DropPoolDMWeak::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolDMGeneric::create(properties),
	{
		AlchemyPoolTier3::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolDMWeak::~DropPoolDMWeak()
{
}
