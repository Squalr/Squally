#include "ShopPoolInnT1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT1::MapKey = "shop-pool-inn-t1";
const std::string ShopPoolInnT1::PoolName = "shop-pool-inn-t1";

ShopPoolInnT1* ShopPoolInnT1::create(ValueMap& properties)
{
	ShopPoolInnT1* instance = new ShopPoolInnT1(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT1::ShopPoolInnT1(ValueMap& properties) : super(properties, ShopPoolInnT1::PoolName,
	{ CardPoolTier1::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT1::~ShopPoolInnT1()
{
}
