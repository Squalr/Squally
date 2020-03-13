#include "BlueAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BlueAxePlans::SaveKeyBlueAxePlans = "blue-axe-plans";

BlueAxePlans* BlueAxePlans::create()
{
	BlueAxePlans* instance = new BlueAxePlans();

	instance->autorelease();

	return instance;
}

BlueAxePlans::BlueAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BlueAxePlans::~BlueAxePlans()
{
}

Item* BlueAxePlans::craft()
{
	return BlueAxe::create();
}

std::map<Item*, int> BlueAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* BlueAxePlans::clone()
{
	return BlueAxePlans::create();
}

std::string BlueAxePlans::getItemName()
{
	return BlueAxePlans::SaveKeyBlueAxePlans;
}

LocalizedString* BlueAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BlueAxe::create();
}

std::string BlueAxePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string BlueAxePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_BlueAxe;
}

std::string BlueAxePlans::getSerializationKey()
{
	return BlueAxePlans::SaveKeyBlueAxePlans;
}
