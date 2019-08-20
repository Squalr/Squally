#include "Impaler.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Spears/Impaler.h"

using namespace cocos2d;

const std::string Impaler::SaveKeyImpaler = "impaler";

Impaler* Impaler::create()
{
	Impaler* instance = new Impaler();

	instance->autorelease();

	return instance;
}

Impaler::Impaler() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

Impaler::~Impaler()
{
}

Item* Impaler::clone()
{
	return Impaler::create();
}

std::string Impaler::getItemName()
{
	return Impaler::SaveKeyImpaler;
}

LocalizedString* Impaler::getString()
{
	return Strings::Items_Equipment_Weapons_Spears_Impaler::create();
}

std::string Impaler::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Spears_Impaler;
}

std::string Impaler::getSerializationKey()
{
	return Impaler::SaveKeyImpaler;
}

Vec2 Impaler::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
