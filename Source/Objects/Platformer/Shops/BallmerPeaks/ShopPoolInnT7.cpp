#include "ShopPoolInnT7.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT7::MapKey = "shop-pool-inn-t7";
const std::string ShopPoolInnT7::PoolName = "shop-pool-inn-t7";

ShopPoolInnT7* ShopPoolInnT7::create(ValueMap& properties)
{
	ShopPoolInnT7* instance = new ShopPoolInnT7(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT7::ShopPoolInnT7(ValueMap& properties) : super(properties, ShopPoolInnT7::PoolName,
	{ CardPoolTier3::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT7::~ShopPoolInnT7()
{
}
