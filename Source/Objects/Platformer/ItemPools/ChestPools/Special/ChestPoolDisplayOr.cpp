#include "ChestPoolDisplayOr.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDisplayOr::PoolName = "display-or";

ChestPoolDisplayOr* ChestPoolDisplayOr::create(ValueMap& properties)
{
	ChestPoolDisplayOr* instance = new ChestPoolDisplayOr(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDisplayOr::ChestPoolDisplayOr(ValueMap& properties) : super(
	properties, ChestPoolDisplayOr::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(SpecialOr::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolDisplayOr::~ChestPoolDisplayOr()
{
}
