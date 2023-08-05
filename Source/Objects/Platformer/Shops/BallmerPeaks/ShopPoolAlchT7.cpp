#include "ShopPoolAlchT7.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT7::MapKey = "shop-pool-alch-t7";
const std::string ShopPoolAlchT7::PoolName = "shop-pool-alch-t7";

ShopPoolAlchT7* ShopPoolAlchT7::create(ValueMap& properties)
{
	ShopPoolAlchT7* instance = new ShopPoolAlchT7(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT7::ShopPoolAlchT7(ValueMap& properties) : super(properties, ShopPoolAlchT7::PoolName,
	{ })
{
	this->addItemToPool(ItemChance::create(FrostBerries::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Snowball::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Meteorite::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GunpowderT7::create(), ItemChance::Probability::Guaranteed));

	// Phasing out
	this->addItemToPool(ItemChance::create(BlackBlood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DemonRoot::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(PhoenixFeather::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GunpowderT6::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT7::~ShopPoolAlchT7()
{
}
