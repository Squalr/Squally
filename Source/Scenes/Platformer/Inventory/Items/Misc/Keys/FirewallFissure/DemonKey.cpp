#include "DemonKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonKey::SaveKey = "demon-key";

DemonKey* DemonKey::create()
{
	DemonKey* instance = new DemonKey();

	instance->autorelease();

	return instance;
}

DemonKey::DemonKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

DemonKey::~DemonKey()
{
}

Item* DemonKey::clone()
{
	return DemonKey::create();
}

LocalizedString* DemonKey::getString()
{
	return Strings::Items_Misc_Keys_DemonKey::create();
}

const std::string& DemonKey::getIconResource()
{
	return ItemResources::Keys_KEY_1;
}

const std::string& DemonKey::getIdentifier()
{
	return DemonKey::SaveKey;
}

