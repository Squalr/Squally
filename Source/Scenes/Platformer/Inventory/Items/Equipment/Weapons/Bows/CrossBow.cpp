#include "CrossBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrossBow::SaveKeyCrossBow = "cross-bow";

CrossBow* CrossBow::create()
{
	CrossBow* instance = new CrossBow();

	instance->autorelease();

	return instance;
}

CrossBow::CrossBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 7 }}), 6, 8, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

CrossBow::~CrossBow()
{
}

Item* CrossBow::clone()
{
	return CrossBow::create();
}

std::string CrossBow::getItemName()
{
	return CrossBow::SaveKeyCrossBow;
}

LocalizedString* CrossBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_CrossBow::create();
}

std::string CrossBow::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_CrossBow;
}

std::string CrossBow::getSerializationKey()
{
	return CrossBow::SaveKeyCrossBow;
}

Vec2 CrossBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
