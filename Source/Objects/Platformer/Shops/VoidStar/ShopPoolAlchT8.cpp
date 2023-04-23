#include "ShopPoolAlchT8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolAlchT8::MapKey = "shop-pool-alch-t8";
const std::string ShopPoolAlchT8::PoolName = "shop-pool-alch-t8";

ShopPoolAlchT8* ShopPoolAlchT8::create(ValueMap& properties)
{
	ShopPoolAlchT8* instance = new ShopPoolAlchT8(properties);

	instance->autorelease();

	return instance;
}

ShopPoolAlchT8::ShopPoolAlchT8(ValueMap& properties) : super(properties, ShopPoolAlchT8::PoolName,
	{ })
{
	// Should be phased out, but may as well keep a full shop
	this->addItemToPool(ItemChance::create(BlackBlood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DemonRoot::create(), ItemChance::Probability::Guaranteed));

	this->addItemToPool(ItemChance::create(FrostBerries::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Snowball::create(), ItemChance::Probability::Guaranteed));

	this->addItemToPool(ItemChance::create(VoidFlower::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolAlchT8::~ShopPoolAlchT8()
{
}
