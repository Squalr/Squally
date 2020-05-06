#include "DropPoolURWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/UnderflowRuins/CurrencyPoolURGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolURWeak::PoolName = "ur-weak";

DropPoolURWeak* DropPoolURWeak::create(ValueMap& properties)
{
	DropPoolURWeak* instance = new DropPoolURWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolURWeak::DropPoolURWeak(ValueMap& properties) : super(properties, DropPoolURWeak::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolURGeneric::create(properties),
	{
		AlchemyPoolTier2::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolURWeak::~DropPoolURWeak()
{
}
