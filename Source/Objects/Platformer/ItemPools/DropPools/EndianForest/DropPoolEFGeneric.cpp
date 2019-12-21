#include "DropPoolEFGeneric.h"

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

const std::string DropPoolEFGeneric::PoolName = "ef-generic";

DropPoolEFGeneric* DropPoolEFGeneric::create(ValueMap& properties)
{
	DropPoolEFGeneric* instance = new DropPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

DropPoolEFGeneric::DropPoolEFGeneric(ValueMap& properties) : super(properties, DropPoolEFGeneric::PoolName, SampleMethod::Random, 1, 2,
	{ CardPoolTier1::create(SampleMethod::Random, 1, 1), CraftingPoolTier1::create(SampleMethod::Random, 1, 2), PotionPoolTier1::create(SampleMethod::Random, 1, 1) })
{
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
