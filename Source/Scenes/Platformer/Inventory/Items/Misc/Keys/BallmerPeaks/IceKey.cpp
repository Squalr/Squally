#include "IceKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IceKey::SaveKey = "ice-key";

IceKey* IceKey::create()
{
	IceKey* instance = new IceKey();

	instance->autorelease();

	return instance;
}

IceKey::IceKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

IceKey::~IceKey()
{
}

Item* IceKey::clone()
{
	return IceKey::create();
}

LocalizedString* IceKey::getString()
{
	return Strings::Items_Misc_Keys_IceKey::create();
}

const std::string& IceKey::getIconResource()
{
	return ItemResources::Keys_KEY_1;
}

const std::string& IceKey::getIdentifier()
{
	return IceKey::SaveKey;
}

