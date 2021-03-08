#include "TownKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TownKey::SaveKey = "town-key";

TownKey* TownKey::create()
{
	TownKey* instance = new TownKey();

	instance->autorelease();

	return instance;
}

TownKey::TownKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

TownKey::~TownKey()
{
}

Item* TownKey::clone()
{
	return TownKey::create();
}

const std::string& TownKey::getItemName()
{
	return TownKey::SaveKey;
}

LocalizedString* TownKey::getString()
{
	return Strings::Items_Misc_Keys_TownKey::create();
}

const std::string& TownKey::getIconResource()
{
	return ItemResources::Keys_KEY_6;
}

const std::string& TownKey::getIdentifier()
{
	return TownKey::SaveKey;
}

