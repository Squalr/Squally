#include "ShopPoolSmithT8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT8::MapKey = "shop-pool-smith-t8";
const std::string ShopPoolSmithT8::PoolName = "shop-pool-smith-t8";

ShopPoolSmithT8* ShopPoolSmithT8::create(ValueMap& properties)
{
	ShopPoolSmithT8* instance = new ShopPoolSmithT8(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT8::ShopPoolSmithT8(ValueMap& properties) : super(properties, ShopPoolSmithT8::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DarkWood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(VoidCrystal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Obsidian::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Bone::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(VoidCrystal::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT8::~ShopPoolSmithT8()
{
}
