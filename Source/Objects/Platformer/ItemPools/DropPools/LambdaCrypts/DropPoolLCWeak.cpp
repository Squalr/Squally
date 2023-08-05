#include "DropPoolLCWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/LambdaCrypts/CurrencyPoolLCGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolLCWeak::PoolName = "lc-weak";

DropPoolLCWeak* DropPoolLCWeak::create(ValueMap& properties)
{
	DropPoolLCWeak* instance = new DropPoolLCWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolLCWeak::DropPoolLCWeak(ValueMap& properties) : super(properties, DropPoolLCWeak::PoolName, SampleMethod::Random, 1, 3, CurrencyPoolLCGeneric::create(properties),
	{
		AlchemyPoolTier5::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolLCWeak::~DropPoolLCWeak()
{
}
