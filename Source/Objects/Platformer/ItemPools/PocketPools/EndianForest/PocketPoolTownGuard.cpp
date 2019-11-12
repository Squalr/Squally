#include "PocketPoolTownGuard.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolTownGuard::PoolName = "town-guard";

PocketPoolTownGuard* PocketPoolTownGuard::create(ValueMap& properties)
{
	PocketPoolTownGuard* instance = new PocketPoolTownGuard(properties);

	instance->autorelease();

	return instance;
}

PocketPoolTownGuard::PocketPoolTownGuard(ValueMap& properties) : super(properties, PocketPoolTownGuard::PoolName, 1, 1)
{
	this->addItemToPool(TownKey::create(), 1.0f);
}

PocketPoolTownGuard::~PocketPoolTownGuard()
{
}
