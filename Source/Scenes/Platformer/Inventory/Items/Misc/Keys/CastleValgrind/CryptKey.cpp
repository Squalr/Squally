#include "CryptKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CryptKey::SaveKey = "crypt-key";

CryptKey* CryptKey::create()
{
	CryptKey* instance = new CryptKey();

	instance->autorelease();

	return instance;
}

CryptKey::CryptKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

CryptKey::~CryptKey()
{
}

Item* CryptKey::clone()
{
	return CryptKey::create();
}

LocalizedString* CryptKey::getString()
{
	return Strings::Items_Misc_Keys_CryptKey::create();
}

const std::string& CryptKey::getIconResource()
{
	return ItemResources::Keys_CryptKey;
}

const std::string& CryptKey::getIdentifier()
{
	return CryptKey::SaveKey;
}

