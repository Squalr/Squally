#include "PocketPoolTownGuard.h"

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

const std::string PocketPoolTownGuard::PoolName = "town-guard";

PocketPoolTownGuard* PocketPoolTownGuard::create(ValueMap& properties)
{
	PocketPoolTownGuard* instance = new PocketPoolTownGuard(properties);

	instance->autorelease();

	return instance;
}

PocketPoolTownGuard::PocketPoolTownGuard(ValueMap& properties) : super(properties, PocketPoolTownGuard::PoolName, SampleMethod::Guarantee, 1, 1,
	{ CraftingPoolTier1::create(SampleMethod::Guarantee, 1, 1) })
{
	this->addItemToPool(ItemChance::create(TownKey::create(), ItemChance::Probability::Guaranteed));
}

PocketPoolTownGuard::~PocketPoolTownGuard()
{
}
