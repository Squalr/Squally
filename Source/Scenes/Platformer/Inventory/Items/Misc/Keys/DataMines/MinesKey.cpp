#include "MinesKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MinesKey::SaveKey = "mines-key";

MinesKey* MinesKey::create()
{
	MinesKey* instance = new MinesKey();

	instance->autorelease();

	return instance;
}

MinesKey::MinesKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

MinesKey::~MinesKey()
{
}

Item* MinesKey::clone()
{
	return MinesKey::create();
}

LocalizedString* MinesKey::getString()
{
	return Strings::Items_Misc_Keys_MinesKey::create();
}

const std::string& MinesKey::getIconResource()
{
	return ItemResources::Keys_KEY_3;
}

const std::string& MinesKey::getIdentifier()
{
	return MinesKey::SaveKey;
}

