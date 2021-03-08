#include "MayanGemBlueItem.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MayanGemBlueItem::SaveKey = "mayan-gem-blue";

MayanGemBlueItem* MayanGemBlueItem::create()
{
	MayanGemBlueItem* instance = new MayanGemBlueItem();

	instance->autorelease();

	return instance;
}

MayanGemBlueItem::MayanGemBlueItem() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 0 }}), ItemMeta(1, 1))
{
}

MayanGemBlueItem::~MayanGemBlueItem()
{
}

Item* MayanGemBlueItem::clone()
{
	return MayanGemBlueItem::create();
}

const std::string& MayanGemBlueItem::getItemName()
{
	return MayanGemBlueItem::SaveKey;
}

LocalizedString* MayanGemBlueItem::getString()
{
	return Strings::Items_Misc_Keys_BlueGem::create();
}

const std::string& MayanGemBlueItem::getIconResource()
{
	return ItemResources::Keys_BlueGem;
}

const std::string& MayanGemBlueItem::getIdentifier()
{
	return MayanGemBlueItem::SaveKey;
}

