#include "TownKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TownKey::SaveKeyTownKey = "town-key";

TownKey* TownKey::create()
{
	TownKey* instance = new TownKey();

	instance->autorelease();

	return instance;
}

TownKey::TownKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}))
{
}

TownKey::~TownKey()
{
}

Item* TownKey::clone()
{
	return TownKey::create();
}

std::string TownKey::getItemName()
{
	return TownKey::SaveKeyTownKey;
}

LocalizedString* TownKey::getString()
{
	return Strings::Items_Misc_Keys_TownKey::create();
}

std::string TownKey::getIconResource()
{
	return ItemResources::Keys_KEY_1;
}

std::string TownKey::getSerializationKey()
{
	return TownKey::SaveKeyTownKey;
}

