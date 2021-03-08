#include "Sulfur.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Sulfur::SaveKey = "sulfur";

Sulfur* Sulfur::create()
{
	Sulfur* instance = new Sulfur();

	instance->autorelease();

	return instance;
}

Sulfur::Sulfur() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 144 }}), ItemMeta(20000))
{
}

Sulfur::~Sulfur()
{
}

Item* Sulfur::clone()
{
	return Sulfur::create();
}

const std::string& Sulfur::getItemName()
{
	return Sulfur::SaveKey;
}

LocalizedString* Sulfur::getString()
{
	return Strings::Items_Crafting_Ore_Sulfur::create();
}

const std::string& Sulfur::getIconResource()
{
	return ItemResources::Crafting_Smithing_Sulfur;
}

const std::string& Sulfur::getIdentifier()
{
	return Sulfur::SaveKey;
}
