#include "ChestPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CraftingPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
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
	properties, ChestPoolEFGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{ CardPoolTier1::create(SampleMethod::Random, 1, 1), CraftingPoolTier1::create(SampleMethod::Guarantee, 2, 3), PotionPoolTier1::create(SampleMethod::Random, 1, 1) })
{
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
