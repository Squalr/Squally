#include "DropPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolEFGeneric::PoolName = "ef-generic";

DropPoolEFGeneric* DropPoolEFGeneric::create(ValueMap& properties)
{
	DropPoolEFGeneric* instance = new DropPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolEFGeneric::DropPoolEFGeneric(ValueMap& properties) : super(properties, DropPoolEFGeneric::PoolName, SampleMethod::Random, 1, 2, { CardPoolTier1Low::create() })
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenMallet::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(WoodCutter::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(CompositeBow::create(), ItemChance::Probability::Epic));
}

DropPoolEFGeneric::~DropPoolEFGeneric()
{
}

void DropPoolEFGeneric::onEnter()
{
	super::onEnter(); 
}

void DropPoolEFGeneric::initializePositions()
{
	super::initializePositions();
}

void DropPoolEFGeneric::initializeListeners()
{
	super::initializeListeners();
}
