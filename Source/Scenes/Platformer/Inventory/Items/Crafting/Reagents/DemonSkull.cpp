#include "DemonSkull.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonSkull::SaveKey = "demon-skull";

DemonSkull* DemonSkull::create()
{
	DemonSkull* instance = new DemonSkull();

	instance->autorelease();

	return instance;
}

DemonSkull::DemonSkull() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 35 }}), ItemMeta(20000))
{
}

DemonSkull::~DemonSkull()
{
}

Item* DemonSkull::clone()
{
	return DemonSkull::create();
}

const std::string& DemonSkull::getItemName()
{
	return DemonSkull::SaveKey;
}

LocalizedString* DemonSkull::getString()
{
	return Strings::Items_Crafting_Reagents_DemonSkull::create();
}

const std::string& DemonSkull::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Reagents_DemonSkull;
}

const std::string& DemonSkull::getIdentifier()
{
	return DemonSkull::SaveKey;
}
