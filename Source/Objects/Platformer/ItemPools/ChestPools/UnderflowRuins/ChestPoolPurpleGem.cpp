#include "ChestPoolPurpleGem.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolPurpleGem::PoolName = "ur-gem-purple";

ChestPoolPurpleGem* ChestPoolPurpleGem::create(ValueMap& properties)
{
	ChestPoolPurpleGem* instance = new ChestPoolPurpleGem(properties);

	instance->autorelease();

	return instance;
}

ChestPoolPurpleGem::ChestPoolPurpleGem(ValueMap& properties) : super(
	properties, ChestPoolPurpleGem::PoolName, SampleMethod::Guarantee, 1, 1,
	{ })
{
	this->addItemToPool(ItemChance::create(MayanGemPurpleItem::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolPurpleGem::~ChestPoolPurpleGem()
{
}
