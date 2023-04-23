#include "ShopPoolAlchT1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT1::MapKey = "shop-pool-alch-t1";
const std::string ShopPoolAlchT1::PoolName = "shop-pool-alch-t1";

ShopPoolAlchT1* ShopPoolAlchT1::create(ValueMap& properties)
{
	ShopPoolAlchT1* instance = new ShopPoolAlchT1(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT1::ShopPoolAlchT1(ValueMap& properties) : super(properties, ShopPoolAlchT1::PoolName)
{
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));

	// Phasing in
	this->addItemToPool(ItemChance::create(Acorn::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT1::~ShopPoolAlchT1()
{
}
