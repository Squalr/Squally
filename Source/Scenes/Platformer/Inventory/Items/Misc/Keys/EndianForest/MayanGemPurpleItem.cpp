#include "MayanGemPurpleItem.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MayanGemPurpleItem::SaveKey = "mayan-gem-purple";

MayanGemPurpleItem* MayanGemPurpleItem::create()
{
	MayanGemPurpleItem* instance = new MayanGemPurpleItem();

	instance->autorelease();

	return instance;
}

MayanGemPurpleItem::MayanGemPurpleItem() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 0 }}), ItemMeta(1, 1))
{
}

MayanGemPurpleItem::~MayanGemPurpleItem()
{
}

Item* MayanGemPurpleItem::clone()
{
	return MayanGemPurpleItem::create();
}

const std::string& MayanGemPurpleItem::getItemName()
{
	return MayanGemPurpleItem::SaveKey;
}

LocalizedString* MayanGemPurpleItem::getString()
{
	return Strings::Items_Misc_Keys_PurpleGem::create();
}

const std::string& MayanGemPurpleItem::getIconResource()
{
	return ItemResources::Keys_PurpleGem;
}

const std::string& MayanGemPurpleItem::getIdentifier()
{
	return MayanGemPurpleItem::SaveKey;
}

