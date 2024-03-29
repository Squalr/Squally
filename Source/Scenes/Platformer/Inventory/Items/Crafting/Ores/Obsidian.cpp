#include "Obsidian.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Obsidian::SaveKey = "obsidian";

Obsidian* Obsidian::create()
{
	Obsidian* instance = new Obsidian();

	instance->autorelease();

	return instance;
}

Obsidian::Obsidian() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 8 * 8 }}), ItemMeta(20000))
{
}

Obsidian::~Obsidian()
{
}

Item* Obsidian::clone()
{
	return Obsidian::create();
}

LocalizedString* Obsidian::getString()
{
	return Strings::Items_Crafting_Ore_Obsidian::create();
}

const std::string& Obsidian::getIconResource()
{
	return ItemResources::Crafting_Smithing_T8_Obsidian;
}

const std::string& Obsidian::getIdentifier()
{
	return Obsidian::SaveKey;
}
