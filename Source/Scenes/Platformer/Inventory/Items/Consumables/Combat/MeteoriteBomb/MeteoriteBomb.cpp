#include "MeteoriteBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/MeteoriteBomb/ThrowMeteoriteBomb.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MeteoriteBomb::SaveKey = "meteorite-bomb";
const int MeteoriteBomb::DamageMin = 70;
const int MeteoriteBomb::DamageMax = 75;

MeteoriteBomb* MeteoriteBomb::create()
{
	MeteoriteBomb* instance = new MeteoriteBomb();

	instance->autorelease();

	return instance;
}

MeteoriteBomb::MeteoriteBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 75 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

MeteoriteBomb::~MeteoriteBomb()
{
}

bool MeteoriteBomb::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

Item* MeteoriteBomb::clone()
{
	return MeteoriteBomb::create();
}

LocalizedString* MeteoriteBomb::getString()
{
	return Strings::Items_Consumables_Combat_MeteoriteBomb::create();
}

const std::string& MeteoriteBomb::getIconResource()
{
	return ItemResources::Consumables_Combat_T7_MeteoriteBomb;
}

const std::string& MeteoriteBomb::getIdentifier()
{
	return MeteoriteBomb::SaveKey;
}

PlatformerAttack* MeteoriteBomb::createAssociatedAttack()
{
	return ThrowMeteoriteBomb::create(PlatformerAttack::Priority::Common);
}
