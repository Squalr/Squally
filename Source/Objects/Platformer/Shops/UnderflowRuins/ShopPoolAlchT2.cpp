#include "ShopPoolAlchT2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT2::MapKey = "shop-pool-alch-t2";
const std::string ShopPoolAlchT2::PoolName = "shop-pool-alch-t2";

ShopPoolAlchT2* ShopPoolAlchT2::create(ValueMap& properties)
{
	ShopPoolAlchT2* instance = new ShopPoolAlchT2(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT2::ShopPoolAlchT2(ValueMap& properties) : super(properties, ShopPoolAlchT2::PoolName,
	{ })
{
	// Phasing out
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));

	this->addItemToPool(ItemChance::create(Acorn::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));

	// Phasing in
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SandRoot::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT2::~ShopPoolAlchT2()
{
}
