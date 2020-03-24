#include "ChestPoolBlueGem.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolBlueGem::PoolName = "ur-gem-blue";

ChestPoolBlueGem* ChestPoolBlueGem::create(ValueMap& properties)
{
	ChestPoolBlueGem* instance = new ChestPoolBlueGem(properties);

	instance->autorelease();

	return instance;
}

ChestPoolBlueGem::ChestPoolBlueGem(ValueMap& properties) : super(
	properties, ChestPoolBlueGem::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(MayanGemBlueItem::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolBlueGem::~ChestPoolBlueGem()
{
}
