#include "HexusPoolMarcel.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/EndianForest/MagesGuildPrisonKey.h"

using namespace cocos2d;

HexusPoolMarcel* HexusPoolMarcel::create()
{
	HexusPoolMarcel* instance = new HexusPoolMarcel();

	instance->autorelease();

	return instance;
}

HexusPoolMarcel::HexusPoolMarcel() : super(ValueMap(), "hexus-pool-marcel", 2, 2)
{
	this->addItemToPool(ItemChance::create(MagesGuildPrisonKey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SpecialMov::create(), ItemChance::Probability::Guaranteed));
}

HexusPoolMarcel::~HexusPoolMarcel()
{
}
