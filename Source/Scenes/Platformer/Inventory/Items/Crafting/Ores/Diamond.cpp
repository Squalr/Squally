#include "Diamond.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Diamond::SaveKeyDiamond = "diamond";

Diamond* Diamond::create()
{
	Diamond* instance = new Diamond();

	instance->autorelease();

	return instance;
}

Diamond::Diamond() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Diamond::~Diamond()
{
}

Item* Diamond::clone()
{
	return Diamond::create();
}

std::string Diamond::getItemName()
{
	return Diamond::SaveKeyDiamond;
}

LocalizedString* Diamond::getString()
{
	return Strings::Items_Crafting_Ore_Diamond::create();
}

std::string Diamond::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Diamond;
}

std::string Diamond::getSerializationKey()
{
	return Diamond::SaveKeyDiamond;
}
