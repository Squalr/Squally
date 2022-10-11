#include "MageTowerKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MageTowerKey::SaveKey = "mage-tower-key";

MageTowerKey* MageTowerKey::create()
{
	MageTowerKey* instance = new MageTowerKey();

	instance->autorelease();

	return instance;
}

MageTowerKey::MageTowerKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

MageTowerKey::~MageTowerKey()
{
}

Item* MageTowerKey::clone()
{
	return MageTowerKey::create();
}

LocalizedString* MageTowerKey::getString()
{
	return Strings::Items_Misc_Keys_MageTowerKey::create();
}

const std::string& MageTowerKey::getIconResource()
{
	return ItemResources::Keys_MageTowerKey;
}

const std::string& MageTowerKey::getIdentifier()
{
	return MageTowerKey::SaveKey;
}

