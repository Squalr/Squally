#include "ChestPoolDMGodiva.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDMGodiva::PoolName = "dm-godiva";

ChestPoolDMGodiva* ChestPoolDMGodiva::create(ValueMap& properties)
{
	ChestPoolDMGodiva* instance = new ChestPoolDMGodiva(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDMGodiva::ChestPoolDMGodiva(ValueMap& properties) : super(
	properties, ChestPoolDMGodiva::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(EmeraldPendant::create(), ItemChance::Probability::VeryCommon));
} 

ChestPoolDMGodiva::~ChestPoolDMGodiva()
{
}
