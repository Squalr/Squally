#include "ShopPoolGriffin.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolGriffin::MapKey = "shop-pool-griffin";
const std::string ShopPoolGriffin::PoolName = "shop-pool-griffin";

ShopPoolGriffin* ShopPoolGriffin::create(ValueMap& properties)
{
	ShopPoolGriffin* instance = new ShopPoolGriffin(properties);

	instance->autorelease();

	return instance;
}

ShopPoolGriffin::ShopPoolGriffin(ValueMap& properties) : super(properties, ShopPoolGriffin::PoolName,
	{ CardPoolTier2::create(SampleMethod::Guarantee, 2, 2) })
{
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolGriffin::~ShopPoolGriffin()
{
}

void ShopPoolGriffin::onEnter()
{
	super::onEnter(); 
}

void ShopPoolGriffin::initializePositions()
{
	super::initializePositions();
}

void ShopPoolGriffin::initializeListeners()
{
	super::initializeListeners();
}
