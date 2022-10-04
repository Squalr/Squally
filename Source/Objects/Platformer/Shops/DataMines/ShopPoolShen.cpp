#include "ShopPoolShen.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolShen::MapKey = "shop-pool-shen";
const std::string ShopPoolShen::PoolName = "shop-pool-shen";

ShopPoolShen* ShopPoolShen::create(ValueMap& properties)
{
	ShopPoolShen* instance = new ShopPoolShen(properties);

	instance->autorelease();

	return instance;
}

ShopPoolShen::ShopPoolShen(ValueMap& properties) : super(properties, ShopPoolShen::PoolName,
	{ CardPoolTier3::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolShen::~ShopPoolShen()
{
}
