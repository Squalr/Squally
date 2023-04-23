#include "SmallBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/SmallBomb/ThrowSmallBomb.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SmallBomb::SaveKey = "small-bomb";
const int SmallBomb::DamageMin = 10;
const int SmallBomb::DamageMax = 14;

SmallBomb* SmallBomb::create()
{
	SmallBomb* instance = new SmallBomb();

	instance->autorelease();

	return instance;
}

SmallBomb::SmallBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 14 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

SmallBomb::~SmallBomb()
{
}

bool SmallBomb::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

Item* SmallBomb::clone()
{
	return SmallBomb::create();
}

LocalizedString* SmallBomb::getString()
{
	return Strings::Items_Consumables_Combat_SmallBomb::create();
}

const std::string& SmallBomb::getIconResource()
{
	return ItemResources::Consumables_Combat_T1_SmallBomb;
}

const std::string& SmallBomb::getIdentifier()
{
	return SmallBomb::SaveKey;
}

PlatformerAttack* SmallBomb::createAssociatedAttack()
{
	return ThrowSmallBomb::create(PlatformerAttack::Priority::Common);
}
