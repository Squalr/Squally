#include "Sulfur.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Sulfur::SaveKeySulfur = "sulfur";

Sulfur* Sulfur::create()
{
	Sulfur* instance = new Sulfur();

	instance->autorelease();

	return instance;
}

Sulfur::Sulfur() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Sulfur::~Sulfur()
{
}

Item* Sulfur::clone()
{
	return Sulfur::create();
}

std::string Sulfur::getItemName()
{
	return Sulfur::SaveKeySulfur;
}

LocalizedString* Sulfur::getString()
{
	return Strings::Items_Crafting_Ore_Sulfur::create();
}

std::string Sulfur::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Sulfur;
}

std::string Sulfur::getSerializationKey()
{
	return Sulfur::SaveKeySulfur;
}
