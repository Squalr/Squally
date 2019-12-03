#include "HexusPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolEFGeneric* HexusPoolEFGeneric::create()
{
	HexusPoolEFGeneric* instance = new HexusPoolEFGeneric();

	instance->autorelease();

	return instance;
}

HexusPoolEFGeneric::HexusPoolEFGeneric() : super(ValueMap(), "hexus-pool-ef-generic", SampleMethod::Random, 1, 2, { CardPoolTier1::create(1) })
{
	// TODO: Crafting materials?
	this->addItemToPool(ItemChance::create(MissingNo::create(), ItemChance::Probability::Guaranteed));
}

HexusPoolEFGeneric::~HexusPoolEFGeneric()
{
}
