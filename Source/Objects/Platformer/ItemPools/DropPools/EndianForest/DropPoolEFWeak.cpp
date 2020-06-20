#include "DropPoolEFWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/EndianForest/CurrencyPoolEFGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/AlchemyPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolEFWeak::PoolName = "ef-weak";

DropPoolEFWeak* DropPoolEFWeak::create(ValueMap& properties)
{
	DropPoolEFWeak* instance = new DropPoolEFWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolEFWeak::DropPoolEFWeak(ValueMap& properties) : super(properties, DropPoolEFWeak::PoolName, SampleMethod::Random, 1, 2, CurrencyPoolEFGeneric::create(properties),
	{
		AlchemyPoolTier1::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolEFWeak::~DropPoolEFWeak()
{
}
