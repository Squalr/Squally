#include "ChestPoolURMirror.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"

using namespace cocos2d;

const std::string ChestPoolURMirror::PoolName = "ur-mirror";

ChestPoolURMirror* ChestPoolURMirror::create(ValueMap& properties)
{
	ChestPoolURMirror* instance = new ChestPoolURMirror(properties);

	instance->autorelease();

	return instance;
}

ChestPoolURMirror::ChestPoolURMirror(ValueMap& properties) : super(
	properties, ChestPoolURMirror::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(MedusaMirror::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolURMirror::~ChestPoolURMirror()
{
}
