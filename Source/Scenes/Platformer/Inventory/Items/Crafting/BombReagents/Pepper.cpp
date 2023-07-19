#include "Pepper.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Pepper::SaveKey = "pepper";

Pepper* Pepper::create()
{
	Pepper* instance = new Pepper();

	instance->autorelease();

	return instance;
}

Pepper::Pepper() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 12 }}), ItemMeta(20000))
{
}

Pepper::~Pepper()
{
}

Item* Pepper::clone()
{
	return Pepper::create();
}

LocalizedString* Pepper::getString()
{
	return Strings::Items_Crafting_BombReagents_Pepper::create();
}

const std::string& Pepper::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T4_Pepper;
}

const std::string& Pepper::getIdentifier()
{
	return Pepper::SaveKey;
}
