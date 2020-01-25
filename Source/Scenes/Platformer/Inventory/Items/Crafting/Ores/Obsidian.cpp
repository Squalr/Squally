#include "Obsidian.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Obsidian::SaveKeyObsidian = "obsidian";

Obsidian* Obsidian::create()
{
	Obsidian* instance = new Obsidian();

	instance->autorelease();

	return instance;
}

Obsidian::Obsidian() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(20000))
{
}

Obsidian::~Obsidian()
{
}

Item* Obsidian::clone()
{
	return Obsidian::create();
}

std::string Obsidian::getItemName()
{
	return Obsidian::SaveKeyObsidian;
}

LocalizedString* Obsidian::getString()
{
	return Strings::Items_Crafting_Ore_Obsidian::create();
}

std::string Obsidian::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Obsidian;
}

std::string Obsidian::getSerializationKey()
{
	return Obsidian::SaveKeyObsidian;
}
