#include "ShopPoolPolyphemus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolPolyphemus::MapKey = "shop-pool-polyphemus";
const std::string ShopPoolPolyphemus::PoolName = "shop-pool-polyphemus";

ShopPoolPolyphemus* ShopPoolPolyphemus::create(ValueMap& properties)
{
	ShopPoolPolyphemus* instance = new ShopPoolPolyphemus(properties);

	instance->autorelease();

	return instance;
}

ShopPoolPolyphemus::ShopPoolPolyphemus(ValueMap& properties) : super(properties, ShopPoolPolyphemus::PoolName,
	{ CardPoolTier1::create(SampleMethod::Guarantee, 6, 6) })
{
}

ShopPoolPolyphemus::~ShopPoolPolyphemus()
{
}

void ShopPoolPolyphemus::onEnter()
{
	super::onEnter(); 
}

void ShopPoolPolyphemus::initializePositions()
{
	super::initializePositions();
}

void ShopPoolPolyphemus::initializeListeners()
{
	super::initializeListeners();
}
