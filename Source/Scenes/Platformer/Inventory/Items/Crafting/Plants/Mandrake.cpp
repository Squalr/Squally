#include "Mandrake.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mandrake::SaveKey = "mandrake";

Mandrake* Mandrake::create()
{
	Mandrake* instance = new Mandrake();

	instance->autorelease();

	return instance;
}

Mandrake::Mandrake() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 74 }}), ItemMeta(20000))
{
}

Mandrake::~Mandrake()
{
}

Item* Mandrake::clone()
{
	return Mandrake::create();
}

LocalizedString* Mandrake::getString()
{
	return Strings::Items_Crafting_Plants_Mandrake::create();
}

const std::string& Mandrake::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Plants_Mandrake;
}

const std::string& Mandrake::getIdentifier()
{
	return Mandrake::SaveKey;
}
