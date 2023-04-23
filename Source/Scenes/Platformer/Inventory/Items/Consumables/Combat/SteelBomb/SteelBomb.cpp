#include "SteelBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/SteelBomb/ThrowSteelBomb.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelBomb::SaveKey = "steel-bomb";
const int SteelBomb::DamageMin = 20;
const int SteelBomb::DamageMax = 24;

SteelBomb* SteelBomb::create()
{
	SteelBomb* instance = new SteelBomb();

	instance->autorelease();

	return instance;
}

SteelBomb::SteelBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 24 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

SteelBomb::~SteelBomb()
{
}

bool SteelBomb::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

Item* SteelBomb::clone()
{
	return SteelBomb::create();
}

LocalizedString* SteelBomb::getString()
{
	return Strings::Items_Consumables_Combat_SteelBomb::create();
}

const std::string& SteelBomb::getIconResource()
{
	return ItemResources::Consumables_Combat_T2_SteelBomb;
}

const std::string& SteelBomb::getIdentifier()
{
	return SteelBomb::SaveKey;
}

PlatformerAttack* SteelBomb::createAssociatedAttack()
{
	return ThrowSteelBomb::create(PlatformerAttack::Priority::Common);
}
