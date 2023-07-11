#include "ShopPoolSmithT6.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT6::MapKey = "shop-pool-smith-t6";
const std::string ShopPoolSmithT6::PoolName = "shop-pool-smith-t6";

ShopPoolSmithT6* ShopPoolSmithT6::create(ValueMap& properties)
{
	ShopPoolSmithT6* instance = new ShopPoolSmithT6(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT6::ShopPoolSmithT6(ValueMap& properties) : super(properties, ShopPoolSmithT6::PoolName, { })
{
	// Phasing in
	this->addItemToPool(ItemChance::create(Sulfur::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Guaranteed));
	
	// Phasing out
	this->addItemToPool(ItemChance::create(Bone::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Guaranteed));

	// Universal
	this->addItemToPool(ItemChance::create(DarkWood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT6::~ShopPoolSmithT6()
{
}
