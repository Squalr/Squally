#include "Ruby.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Ruby::SaveKeyRuby = "ruby";

Ruby* Ruby::create()
{
	Ruby* instance = new Ruby();

	instance->autorelease();

	return instance;
}

Ruby::Ruby() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Ruby::~Ruby()
{
}

Item* Ruby::clone()
{
	return Ruby::create();
}

std::string Ruby::getItemName()
{
	return Ruby::SaveKeyRuby;
}

LocalizedString* Ruby::getString()
{
	return Strings::Items_Crafting_Ore_Ruby::create();
}

std::string Ruby::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Ruby;
}

std::string Ruby::getSerializationKey()
{
	return Ruby::SaveKeyRuby;
}
