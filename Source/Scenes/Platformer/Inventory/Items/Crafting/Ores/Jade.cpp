#include "Jade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Jade::SaveKeyJade = "jade";

Jade* Jade::create()
{
	Jade* instance = new Jade();

	instance->autorelease();

	return instance;
}

Jade::Jade() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(20000))
{
}

Jade::~Jade()
{
}

Item* Jade::clone()
{
	return Jade::create();
}

std::string Jade::getItemName()
{
	return Jade::SaveKeyJade;
}

LocalizedString* Jade::getString()
{
	return Strings::Items_Crafting_Ore_Jade::create();
}

std::string Jade::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Jade;
}

std::string Jade::getSerializationKey()
{
	return Jade::SaveKeyJade;
}
