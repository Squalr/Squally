#include "ShopPoolInnT4.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/CardPoolTier4.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT4::MapKey = "shop-pool-inn-t4";
const std::string ShopPoolInnT4::PoolName = "shop-pool-inn-t4";

ShopPoolInnT4* ShopPoolInnT4::create(ValueMap& properties)
{
	ShopPoolInnT4* instance = new ShopPoolInnT4(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT4::ShopPoolInnT4(ValueMap& properties) : super(properties, ShopPoolInnT4::PoolName,
	{ CardPoolTier4::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT4::~ShopPoolInnT4()
{
}
