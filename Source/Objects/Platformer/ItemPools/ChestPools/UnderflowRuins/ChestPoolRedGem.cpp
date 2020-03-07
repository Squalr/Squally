#include "ChestPoolRedGem.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolRedGem::PoolName = "ur-gem-red";

ChestPoolRedGem* ChestPoolRedGem::create(ValueMap& properties)
{
	ChestPoolRedGem* instance = new ChestPoolRedGem(properties);

	instance->autorelease();

	return instance;
}

ChestPoolRedGem::ChestPoolRedGem(ValueMap& properties) : super(
	properties, ChestPoolRedGem::PoolName, SampleMethod::Guarantee, 1, 1,
	{ })
{
	this->addItemToPool(ItemChance::create(MayanGemRedItem::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolRedGem::~ChestPoolRedGem()
{
}
