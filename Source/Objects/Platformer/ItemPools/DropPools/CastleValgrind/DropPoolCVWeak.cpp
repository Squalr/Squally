#include "DropPoolCVWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/CastleValgrind/CurrencyPoolCVGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/AlchemyPoolTier4.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolCVWeak::PoolName = "cv-weak";

DropPoolCVWeak* DropPoolCVWeak::create(ValueMap& properties)
{
	DropPoolCVWeak* instance = new DropPoolCVWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolCVWeak::DropPoolCVWeak(ValueMap& properties) : super(properties, DropPoolCVWeak::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolCVGeneric::create(properties),
	{
		AlchemyPoolTier4::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolCVWeak::~DropPoolCVWeak()
{
}
