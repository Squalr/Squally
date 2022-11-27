#include "DropPoolDHWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/DaemonsHallow/CurrencyPoolDHGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolDHWeak::PoolName = "dh-weak";

DropPoolDHWeak* DropPoolDHWeak::create(ValueMap& properties)
{
	DropPoolDHWeak* instance = new DropPoolDHWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolDHWeak::DropPoolDHWeak(ValueMap& properties) : super(properties, DropPoolDHWeak::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolDHGeneric::create(properties),
	{
		AlchemyPoolTier6::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolDHWeak::~DropPoolDHWeak()
{
}
