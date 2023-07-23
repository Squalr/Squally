#include "RustyKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RustyKey::SaveKey = "rusty-key";

RustyKey* RustyKey::create()
{
	RustyKey* instance = new RustyKey();

	instance->autorelease();

	return instance;
}

RustyKey::RustyKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

RustyKey::~RustyKey()
{
}

Item* RustyKey::clone()
{
	return RustyKey::create();
}

LocalizedString* RustyKey::getString()
{
	return Strings::Items_Misc_Keys_RustyKey::create();
}

const std::string& RustyKey::getIconResource()
{
	return ItemResources::Keys_KEY_1;
}

const std::string& RustyKey::getIdentifier()
{
	return RustyKey::SaveKey;
}

