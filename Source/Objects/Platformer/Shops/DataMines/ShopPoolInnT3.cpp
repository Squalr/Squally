#include "ShopPoolInnT3.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT3::MapKey = "shop-pool-inn-t3";
const std::string ShopPoolInnT3::PoolName = "shop-pool-inn-t3";

ShopPoolInnT3* ShopPoolInnT3::create(ValueMap& properties)
{
	ShopPoolInnT3* instance = new ShopPoolInnT3(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT3::ShopPoolInnT3(ValueMap& properties) : super(properties, ShopPoolInnT3::PoolName,
	{ CardPoolTier3::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT3::~ShopPoolInnT3()
{
}
