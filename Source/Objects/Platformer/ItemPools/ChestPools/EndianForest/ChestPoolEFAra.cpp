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
	properties, ChestPoolEFAra::PoolName, SampleMethod::Guarantee, 3, 3,
	{
	})
{
	this->addItemToPool(ItemChance::create(JoustingHelmet::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Monocle::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(LeatherCap::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolEFAra::~ChestPoolEFAra()
{
}
