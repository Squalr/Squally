#include "Eggplant.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Eggplant::SaveKey = "eggplant";

Eggplant* Eggplant::create()
{
	Eggplant* instance = new Eggplant();

	instance->autorelease();

	return instance;
}

Eggplant::Eggplant() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), ItemMeta(20000))
{
}

Eggplant::~Eggplant()
{
}

Item* Eggplant::clone()
{
	return Eggplant::create();
}

const std::string& Eggplant::getItemName()
{
	return Eggplant::SaveKey;
}

LocalizedString* Eggplant::getString()
{
	return Strings::Items_Crafting_Reagents_Eggplant::create();
}

const std::string& Eggplant::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Reagents_Eggplant;
}

const std::string& Eggplant::getIdentifier()
{
	return Eggplant::SaveKey;
}
