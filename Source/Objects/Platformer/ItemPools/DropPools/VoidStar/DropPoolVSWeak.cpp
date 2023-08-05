#include "DropPoolVSWeak.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/VoidStar/CurrencyPoolVSGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/AlchemyPoolTier8.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolVSWeak::PoolName = "vs-weak";

DropPoolVSWeak* DropPoolVSWeak::create(ValueMap& properties)
{
	DropPoolVSWeak* instance = new DropPoolVSWeak(properties);

	instance->autorelease();

	return instance;
}

DropPoolVSWeak::DropPoolVSWeak(ValueMap& properties) : super(properties, DropPoolVSWeak::PoolName, SampleMethod::Random, 1, 3, CurrencyPoolVSGeneric::create(properties),
	{
		AlchemyPoolTier8::create(SampleMethod::Guarantee, 1, 1),
	})
{
}

DropPoolVSWeak::~DropPoolVSWeak()
{
}
