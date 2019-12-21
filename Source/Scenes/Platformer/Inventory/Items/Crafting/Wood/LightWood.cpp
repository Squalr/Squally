#include "LightWood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LightWood::SaveKeyLightWood = "light-wood";

LightWood* LightWood::create()
{
	LightWood* instance = new LightWood();

	instance->autorelease();

	return instance;
}

LightWood::LightWood() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

LightWood::~LightWood()
{
}

Item* LightWood::clone()
{
	return LightWood::create();
}

std::string LightWood::getItemName()
{
	return LightWood::SaveKeyLightWood;
}

LocalizedString* LightWood::getString()
{
	return Strings::Items_Crafting_Wood_LightWood::create();
}

std::string LightWood::getIconResource()
{
	return ObjectResources::Items_Reagents_Wood_LightWood;
}

std::string LightWood::getSerializationKey()
{
	return LightWood::SaveKeyLightWood;
}
