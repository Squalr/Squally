#include "DropPoolBPWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/BallmerPeaks/CurrencyPoolBPGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/AlchemyPoolTier7.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolBPWeak::PoolName = "bp-weak";

DropPoolBPWeak* DropPoolBPWeak::create(ValueMap& properties)
{
	DropPoolBPWeak* instance = new DropPoolBPWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolBPWeak::DropPoolBPWeak(ValueMap& properties) : super(properties, DropPoolBPWeak::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolBPGeneric::create(properties),
	{
		AlchemyPoolTier7::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolBPWeak::~DropPoolBPWeak()
{
}
