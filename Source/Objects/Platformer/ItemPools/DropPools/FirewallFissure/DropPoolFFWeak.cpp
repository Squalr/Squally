#include "DropPoolFFWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/FirewallFissure/CurrencyPoolFFGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolFFWeak::PoolName = "ff-weak";

DropPoolFFWeak* DropPoolFFWeak::create(ValueMap& properties)
{
	DropPoolFFWeak* instance = new DropPoolFFWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolFFWeak::DropPoolFFWeak(ValueMap& properties) : super(properties, DropPoolFFWeak::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolFFGeneric::create(properties),
	{
		AlchemyPoolTier6::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolFFWeak::~DropPoolFFWeak()
{
}
