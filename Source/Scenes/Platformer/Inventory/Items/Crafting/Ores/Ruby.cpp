#include "Ruby.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ruby::SaveKey = "ruby";

Ruby* Ruby::create()
{
	Ruby* instance = new Ruby();

	instance->autorelease();

	return instance;
}

Ruby::Ruby() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 133 }}), ItemMeta(20000))
{
}

Ruby::~Ruby()
{
}

Item* Ruby::clone()
{
	return Ruby::create();
}

LocalizedString* Ruby::getString()
{
	return Strings::Items_Crafting_Ore_Ruby::create();
}

const std::string& Ruby::getIconResource()
{
	return ItemResources::Crafting_Smithing_Ruby;
}

const std::string& Ruby::getIdentifier()
{
	return Ruby::SaveKey;
}
