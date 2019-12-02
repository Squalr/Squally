#include "DropPoolError.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string DropPoolError::PoolName = "error";

DropPoolError* DropPoolError::create(ValueMap& properties)
{
	DropPoolError* instance = new DropPoolError(properties);

	instance->autorelease();

	return instance;
}

DropPoolError::DropPoolError(ValueMap& properties) : super(properties, DropPoolError::PoolName, 1, 3, CardPoolTier1::create())
{
	this->addItemToPool(ItemChance::create(MissingNo::create(), ItemChance::Probability::Guaranteed));
}

DropPoolError::~DropPoolError()
{
}

void DropPoolError::onEnter()
{
	super::onEnter(); 
}

void DropPoolError::initializePositions()
{
	super::initializePositions();
}

void DropPoolError::initializeListeners()
{
	super::initializeListeners();
}
