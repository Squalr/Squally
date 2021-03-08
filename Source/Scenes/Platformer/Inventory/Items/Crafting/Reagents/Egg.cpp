#include "Egg.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Egg::SaveKey = "egg";

Egg* Egg::create()
{
	Egg* instance = new Egg();

	instance->autorelease();

	return instance;
}

Egg::Egg() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 6 }}), ItemMeta(20000))
{
}

Egg::~Egg()
{
}

Item* Egg::clone()
{
	return Egg::create();
}

const std::string& Egg::getItemName()
{
	return Egg::SaveKey;
}

LocalizedString* Egg::getString()
{
	return Strings::Items_Crafting_Reagents_Egg::create();
}

const std::string& Egg::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Reagents_Egg;
}

const std::string& Egg::getIdentifier()
{
	return Egg::SaveKey;
}
