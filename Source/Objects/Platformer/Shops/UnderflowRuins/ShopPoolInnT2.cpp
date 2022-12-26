#include "ShopPoolInnT2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT2::MapKey = "shop-pool-inn-t2";
const std::string ShopPoolInnT2::PoolName = "shop-pool-inn-t2";

ShopPoolInnT2* ShopPoolInnT2::create(ValueMap& properties)
{
	ShopPoolInnT2* instance = new ShopPoolInnT2(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT2::ShopPoolInnT2(ValueMap& properties) : super(properties, ShopPoolInnT2::PoolName,
	{ CardPoolTier2::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT2::~ShopPoolInnT2()
{
}
