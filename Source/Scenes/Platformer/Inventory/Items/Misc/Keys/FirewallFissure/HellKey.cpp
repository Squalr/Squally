#include "HellKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HellKey::SaveKey = "hell-key";

HellKey* HellKey::create()
{
	HellKey* instance = new HellKey();

	instance->autorelease();

	return instance;
}

HellKey::HellKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

HellKey::~HellKey()
{
}

Item* HellKey::clone()
{
	return HellKey::create();
}

LocalizedString* HellKey::getString()
{
	return Strings::Items_Misc_Keys_HellKey::create();
}

const std::string& HellKey::getIconResource()
{
	return ItemResources::Keys_KEY_1;
}

const std::string& HellKey::getIdentifier()
{
	return HellKey::SaveKey;
}

