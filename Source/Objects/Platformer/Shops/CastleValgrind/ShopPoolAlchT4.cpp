#include "ShopPoolAlchT4.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT4::MapKey = "shop-pool-alch-t4";
const std::string ShopPoolAlchT4::PoolName = "shop-pool-alch-t4";

ShopPoolAlchT4* ShopPoolAlchT4::create(ValueMap& properties)
{
	ShopPoolAlchT4* instance = new ShopPoolAlchT4(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT4::ShopPoolAlchT4(ValueMap& properties) : super(properties, ShopPoolAlchT4::PoolName,
	{ })
{
	this->addItemToPool(ItemChance::create(GoldWeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(RatTail::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Pepper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GunpowderT4::create(), ItemChance::Probability::Guaranteed));

	// Phasing out
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SandRoot::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(StrongChitin::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GunpowderT3::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT4::~ShopPoolAlchT4()
{
}
