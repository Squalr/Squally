#include "SpeedRune.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Speed/SpeedRune/ThrowSpeedRune.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpeedRune::SaveKeySpeedRune = "speed-rune";

SpeedRune* SpeedRune::create()
{
	SpeedRune* instance = new SpeedRune();

	instance->autorelease();

	return instance;
}

SpeedRune::SpeedRune() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}))
{
}

SpeedRune::~SpeedRune()
{
}

Item* SpeedRune::clone()
{
	return SpeedRune::create();
}

std::string SpeedRune::getItemName()
{
	return SpeedRune::SaveKeySpeedRune;
}

LocalizedString* SpeedRune::getString()
{
	return Strings::Items_Consumables_Speed_SpeedRune::create();
}

std::string SpeedRune::getIconResource()
{
	return ObjectResources::Items_Consumables_Runes_YELLOW_RUNE;
}

std::string SpeedRune::getSerializationKey()
{
	return SpeedRune::SaveKeySpeedRune;
}

PlatformerAttack* SpeedRune::createAssociatedAttack()
{
	return ThrowSpeedRune::create();
}
