#include "ShopPoolInnT5.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/CardPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT5::MapKey = "shop-pool-inn-t5";
const std::string ShopPoolInnT5::PoolName = "shop-pool-inn-t5";

ShopPoolInnT5* ShopPoolInnT5::create(ValueMap& properties)
{
	ShopPoolInnT5* instance = new ShopPoolInnT5(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT5::ShopPoolInnT5(ValueMap& properties) : super(properties, ShopPoolInnT5::PoolName,
	{ CardPoolTier5::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT5::~ShopPoolInnT5()
{
}
