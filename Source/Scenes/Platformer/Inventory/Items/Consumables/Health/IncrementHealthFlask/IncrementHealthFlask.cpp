#include "IncrementHealthFlask.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/ThrowIncrementHealthFlask.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IncrementHealthFlask::SaveKey = "increment-health-flask";
const int IncrementHealthFlask::HealTicks = 8;

IncrementHealthFlask* IncrementHealthFlask::create()
{
	IncrementHealthFlask* instance = new IncrementHealthFlask();

	instance->autorelease();

	return instance;
}

IncrementHealthFlask::IncrementHealthFlask() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20, RubberBanding(3, 0.15f)))
{
}

IncrementHealthFlask::~IncrementHealthFlask()
{
}

Item* IncrementHealthFlask::clone()
{
	return IncrementHealthFlask::create();
}

std::string IncrementHealthFlask::getItemName()
{
	return IncrementHealthFlask::SaveKey;
}

LocalizedString* IncrementHealthFlask::getString()
{
	return Strings::Items_Consumables_Health_IncrementHealthFlask::create();
}

std::string IncrementHealthFlask::getIconResource()
{
	return ItemResources::Consumables_Potions_HealthFlaskIncrement;
}

std::string IncrementHealthFlask::getSerializationKey()
{
	return IncrementHealthFlask::SaveKey;
}

PlatformerAttack* IncrementHealthFlask::createAssociatedAttack()
{
	return ThrowIncrementHealthFlask::create(PlatformerAttack::Priority::Common);
}
