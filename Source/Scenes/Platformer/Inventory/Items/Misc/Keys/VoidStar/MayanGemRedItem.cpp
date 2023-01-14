#include "MayanGemRedItem.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MayanGemRedItem::SaveKey = "mayan-gem-red";

MayanGemRedItem* MayanGemRedItem::create()
{
	MayanGemRedItem* instance = new MayanGemRedItem();

	instance->autorelease();

	return instance;
}

MayanGemRedItem::MayanGemRedItem() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 0 }}), ItemMeta(1, 1))
{
}

MayanGemRedItem::~MayanGemRedItem()
{
}

Item* MayanGemRedItem::clone()
{
	return MayanGemRedItem::create();
}

LocalizedString* MayanGemRedItem::getString()
{
	return Strings::Items_Misc_Keys_RedGem::create();
}

const std::string& MayanGemRedItem::getIconResource()
{
	return ItemResources::Keys_RedGem;
}

const std::string& MayanGemRedItem::getIdentifier()
{
	return MayanGemRedItem::SaveKey;
}

