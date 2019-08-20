#include "SkullCrusher.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/SkullCrusher.h"

using namespace cocos2d;

const std::string SkullCrusher::SaveKeySkullCrusher = "skull-crusher";

SkullCrusher* SkullCrusher::create()
{
	SkullCrusher* instance = new SkullCrusher();

	instance->autorelease();

	return instance;
}

SkullCrusher::SkullCrusher() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

SkullCrusher::~SkullCrusher()
{
}

Item* SkullCrusher::clone()
{
	return SkullCrusher::create();
}

std::string SkullCrusher::getItemName()
{
	return SkullCrusher::SaveKeySkullCrusher;
}

LocalizedString* SkullCrusher::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_SkullCrusher::create();
}

std::string SkullCrusher::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_SkullCrusher;
}

std::string SkullCrusher::getSerializationKey()
{
	return SkullCrusher::SaveKeySkullCrusher;
}

Vec2 SkullCrusher::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
