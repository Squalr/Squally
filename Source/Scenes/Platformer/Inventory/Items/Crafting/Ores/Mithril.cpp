#include "Mithril.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mithril::SaveKey = "mithril";

Mithril* Mithril::create()
{
	Mithril* instance = new Mithril();

	instance->autorelease();

	return instance;
}

Mithril::Mithril() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 44 }}), ItemMeta(20000))
{
}

Mithril::~Mithril()
{
}

Item* Mithril::clone()
{
	return Mithril::create();
}

LocalizedString* Mithril::getString()
{
	return Strings::Items_Crafting_Ore_Mithril::create();
}

const std::string& Mithril::getIconResource()
{
	return ItemResources::Crafting_Smithing_Mithril;
}

const std::string& Mithril::getIdentifier()
{
	return Mithril::SaveKey;
}
