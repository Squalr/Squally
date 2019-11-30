#include "MoonBlade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MoonBlade::SaveKeyMoonBlade = "moon-blade";

MoonBlade* MoonBlade::create()
{
	MoonBlade* instance = new MoonBlade();

	instance->autorelease();

	return instance;
}

MoonBlade::MoonBlade() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

MoonBlade::~MoonBlade()
{
}

Item* MoonBlade::clone()
{
	return MoonBlade::create();
}

std::string MoonBlade::getItemName()
{
	return MoonBlade::SaveKeyMoonBlade;
}

LocalizedString* MoonBlade::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MoonBlade::create();
}

std::string MoonBlade::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_MoonBlade;
}

std::string MoonBlade::getSerializationKey()
{
	return MoonBlade::SaveKeyMoonBlade;
}
