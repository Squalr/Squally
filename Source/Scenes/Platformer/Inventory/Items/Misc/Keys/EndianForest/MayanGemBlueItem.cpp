#include "MayanGemBlueItem.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MayanGemBlueItem::SaveKeyMayanGemBlueItem = "mayan-gem-blue";

MayanGemBlueItem* MayanGemBlueItem::create()
{
	MayanGemBlueItem* instance = new MayanGemBlueItem();

	instance->autorelease();

	return instance;
}

MayanGemBlueItem::MayanGemBlueItem() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 0 }}))
{
}

MayanGemBlueItem::~MayanGemBlueItem()
{
}

Item* MayanGemBlueItem::clone()
{
	return MayanGemBlueItem::create();
}

std::string MayanGemBlueItem::getItemName()
{
	return MayanGemBlueItem::SaveKeyMayanGemBlueItem;
}

LocalizedString* MayanGemBlueItem::getString()
{
	return Strings::Items_Misc_Keys_BlueGem::create();
}

std::string MayanGemBlueItem::getIconResource()
{
	return ObjectResources::Doors_Mayan_BlueGem;
}

std::string MayanGemBlueItem::getSerializationKey()
{
	return MayanGemBlueItem::SaveKeyMayanGemBlueItem;
}

