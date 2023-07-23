#include "FrozenKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrozenKey::SaveKey = "frozen-key";

FrozenKey* FrozenKey::create()
{
	FrozenKey* instance = new FrozenKey();

	instance->autorelease();

	return instance;
}

FrozenKey::FrozenKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

FrozenKey::~FrozenKey()
{
}

Item* FrozenKey::clone()
{
	return FrozenKey::create();
}

LocalizedString* FrozenKey::getString()
{
	return Strings::Items_Misc_Keys_FrozenKey::create();
}

const std::string& FrozenKey::getIconResource()
{
	return ItemResources::Keys_KEY_1;
}

const std::string& FrozenKey::getIdentifier()
{
	return FrozenKey::SaveKey;
}

