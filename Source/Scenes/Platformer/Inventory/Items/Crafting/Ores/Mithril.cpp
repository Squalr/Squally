#include "Mithril.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mithril::SaveKeyMithril = "mithril";

Mithril* Mithril::create()
{
	Mithril* instance = new Mithril();

	instance->autorelease();

	return instance;
}

Mithril::Mithril() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Mithril::~Mithril()
{
}

Item* Mithril::clone()
{
	return Mithril::create();
}

std::string Mithril::getItemName()
{
	return Mithril::SaveKeyMithril;
}

LocalizedString* Mithril::getString()
{
	return Strings::Items_Crafting_Ore_Mithril::create();
}

std::string Mithril::getIconResource()
{
	return ItemResources::Crafting_Smithing_Mithril;
}

std::string Mithril::getSerializationKey()
{
	return Mithril::SaveKeyMithril;
}
