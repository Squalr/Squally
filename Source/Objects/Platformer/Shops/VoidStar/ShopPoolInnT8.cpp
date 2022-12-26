#include "ShopPoolInnT8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolInnT8::MapKey = "shop-pool-inn-t8";
const std::string ShopPoolInnT8::PoolName = "shop-pool-inn-t8";

ShopPoolInnT8* ShopPoolInnT8::create(ValueMap& properties)
{
	ShopPoolInnT8* instance = new ShopPoolInnT8(properties);

	instance->autorelease();

	return instance;
}

ShopPoolInnT8::ShopPoolInnT8(ValueMap& properties) : super(properties, ShopPoolInnT8::PoolName,
	{ CardPoolTier3::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolInnT8::~ShopPoolInnT8()
{
}
