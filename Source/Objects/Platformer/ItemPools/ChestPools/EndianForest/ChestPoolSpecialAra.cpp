#include "ChestPoolSpecialAra.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/WeaponPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolSpecialAra::PoolName = "ef-special-ara";

ChestPoolSpecialAra* ChestPoolSpecialAra::create(ValueMap& properties)
{
	ChestPoolSpecialAra* instance = new ChestPoolSpecialAra(properties);

	instance->autorelease();

	return instance;
}

ChestPoolSpecialAra::ChestPoolSpecialAra(ValueMap& properties) : super(
	properties, ChestPoolSpecialAra::PoolName, SampleMethod::Guarantee, 1, 1,
	{ WeaponPoolTier1::create(SampleMethod::Guarantee, 1, 1) })
{
}

ChestPoolSpecialAra::~ChestPoolSpecialAra()
{
}
