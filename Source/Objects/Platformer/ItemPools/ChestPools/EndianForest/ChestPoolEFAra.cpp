#include "ChestPoolEFAra.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolEFAra::PoolName = "ef-ara";

ChestPoolEFAra* ChestPoolEFAra::create(ValueMap& properties)
{
	ChestPoolEFAra* instance = new ChestPoolEFAra(properties);

	instance->autorelease();

	return instance;
}

ChestPoolEFAra::ChestPoolEFAra(ValueMap& properties) : super(
	properties, ChestPoolEFAra::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(SapphireNecklace::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolEFAra::~ChestPoolEFAra()
{
}
