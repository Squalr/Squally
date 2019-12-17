#include "Dirt.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Dirt::SaveKeyDirt = "dirt";

Dirt* Dirt::create()
{
	Dirt* instance = new Dirt();

	instance->autorelease();

	return instance;
}

Dirt::Dirt() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Dirt::~Dirt()
{
}

Item* Dirt::clone()
{
	return Dirt::create();
}

std::string Dirt::getItemName()
{
	return Dirt::SaveKeyDirt;
}

LocalizedString* Dirt::getString()
{
	return Strings::Items_Crafting_Ore_Dirt::create();
}

std::string Dirt::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Dirt;
}

std::string Dirt::getSerializationKey()
{
	return Dirt::SaveKeyDirt;
}
