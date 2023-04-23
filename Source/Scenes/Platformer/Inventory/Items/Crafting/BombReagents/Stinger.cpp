#include "Stinger.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Stinger::SaveKey = "stinger";

Stinger* Stinger::create()
{
	Stinger* instance = new Stinger();

	instance->autorelease();

	return instance;
}

Stinger::Stinger() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 43 }}), ItemMeta(20000))
{
}

Stinger::~Stinger()
{
}

Item* Stinger::clone()
{
	return Stinger::create();
}

LocalizedString* Stinger::getString()
{
	return Strings::Items_Crafting_BombReagents_Stinger::create();
}

const std::string& Stinger::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T5_Stinger;
}

const std::string& Stinger::getIdentifier()
{
	return Stinger::SaveKey;
}
