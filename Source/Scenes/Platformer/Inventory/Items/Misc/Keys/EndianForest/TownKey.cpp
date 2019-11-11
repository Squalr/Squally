#include "TownKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Misc/Keys/TownKey.h"

using namespace cocos2d;

const std::string TownKey::SaveKeyTownKey = "town-key";

TownKey* TownKey::create()
{
	TownKey* instance = new TownKey();

	instance->autorelease();

	return instance;
}

TownKey::TownKey() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
	return ObjectResources::Items_Misc_KEY_1;
}

std::string TownKey::getSerializationKey()
{
	return TownKey::SaveKeyTownKey;
}

