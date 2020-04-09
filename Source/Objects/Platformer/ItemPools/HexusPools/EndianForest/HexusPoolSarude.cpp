#include "HexusPoolSarude.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/EndianForest/MagesGuildPrisonKey.h"

using namespace cocos2d;

HexusPoolSarude* HexusPoolSarude::create()
{
	HexusPoolSarude* instance = new HexusPoolSarude();

	instance->autorelease();

	return instance;
}

HexusPoolSarude::HexusPoolSarude() : super(ValueMap(), "hexus-pool-marcel", SampleMethod::Guarantee, 2, 2)
{
	this->addItemToPool(ItemChance::create(MagesGuildPrisonKey::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SpecialMov::create(), ItemChance::Probability::Guaranteed));
}

HexusPoolSarude::~HexusPoolSarude()
{
}
