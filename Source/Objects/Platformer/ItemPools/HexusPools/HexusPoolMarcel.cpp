#include "HexusPoolMarcel.h"

#include "cocos/base/CCValue.h"

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
	this->addItemToPool(SpecialMov::create(), 1.00f);
	this->addItemToPool(MagesGuildPrisonKey::create(), 1.00f);
}

HexusPoolMarcel::~HexusPoolMarcel()
{
}
