#include "FrostKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostKey::SaveKey = "frost-key";

FrostKey* FrostKey::create()
{
	FrostKey* instance = new FrostKey();

	instance->autorelease();

	return instance;
}

FrostKey::FrostKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

FrostKey::~FrostKey()
{
}

Item* FrostKey::clone()
{
	return FrostKey::create();
}

LocalizedString* FrostKey::getString()
{
	return Strings::Items_Misc_Keys_FrostKey::create();
}

const std::string& FrostKey::getIconResource()
{
	return ItemResources::Keys_KEY_1;
}

const std::string& FrostKey::getIdentifier()
{
	return FrostKey::SaveKey;
}

