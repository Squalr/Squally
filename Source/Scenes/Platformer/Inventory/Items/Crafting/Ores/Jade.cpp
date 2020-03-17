#include "Jade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Jade::SaveKeyJade = "jade";

Jade* Jade::create()
{
	Jade* instance = new Jade();

	instance->autorelease();

	return instance;
}

Jade::Jade() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Jade::~Jade()
{
}

Item* Jade::clone()
{
	return Jade::create();
}

std::string Jade::getItemName()
{
	return Jade::SaveKeyJade;
}

LocalizedString* Jade::getString()
{
	return Strings::Items_Crafting_Ore_Jade::create();
}

std::string Jade::getIconResource()
{
	return ItemResources::Crafting_Ores_Jade;
}

std::string Jade::getSerializationKey()
{
	return Jade::SaveKeyJade;
}
