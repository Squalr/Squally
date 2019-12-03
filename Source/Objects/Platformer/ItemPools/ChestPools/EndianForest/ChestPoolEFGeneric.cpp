#include "ChestPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Objects/Platformer/ItemPools/ChestPools/EndianForest/WeaponPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ChestPoolEFGeneric::PoolName = "ef-generic";

ChestPoolEFGeneric* ChestPoolEFGeneric::create(ValueMap& properties)
{
	ChestPoolEFGeneric* instance = new ChestPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolEFGeneric::ChestPoolEFGeneric(ValueMap& properties) : super(
	properties, ChestPoolEFGeneric::PoolName, SampleMethod::Guarantee, 1, 1, { CardPoolTier1::create(), WeaponPoolTier1::create(SampleMethod::Random) })
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Common));
}

ChestPoolEFGeneric::~ChestPoolEFGeneric()
{
}

void ChestPoolEFGeneric::onEnter()
{
	super::onEnter(); 
}

void ChestPoolEFGeneric::initializePositions()
{
	super::initializePositions();
}

void ChestPoolEFGeneric::initializeListeners()
{
	super::initializeListeners();
}
