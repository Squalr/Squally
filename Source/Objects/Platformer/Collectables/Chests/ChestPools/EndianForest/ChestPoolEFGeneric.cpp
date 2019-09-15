#include "ChestPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
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

ChestPoolEFGeneric::ChestPoolEFGeneric(ValueMap& properties) : super(properties, ChestPoolEFGeneric::PoolName, 1, 1)
{
	this->addItemToPool(HealthPotion::create(), 1.0f);
	this->addItemToPool(ManaPotion::create(), 1.0f);
	this->addItemToPool(WoodenMallet::create(), 1.0f);
	this->addItemToPool(WoodCutter::create(), 1.0f);
	this->addItemToPool(WoodenWand::create(), 1.0f);
	this->addItemToPool(CompositeBow::create(), 1.0f);
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
