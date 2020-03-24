#include "ChestPoolEFWeapon.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/WeaponPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolEFWeapon::PoolName = "ef-weapon";

ChestPoolEFWeapon* ChestPoolEFWeapon::create(ValueMap& properties)
{
	ChestPoolEFWeapon* instance = new ChestPoolEFWeapon(properties);

	instance->autorelease();

	return instance;
}

ChestPoolEFWeapon::ChestPoolEFWeapon(ValueMap& properties) : super(
	properties, ChestPoolEFWeapon::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		WeaponPoolTier1::create(SampleMethod::Guarantee, 1, 1)
	})
{
}

ChestPoolEFWeapon::~ChestPoolEFWeapon()
{
}
