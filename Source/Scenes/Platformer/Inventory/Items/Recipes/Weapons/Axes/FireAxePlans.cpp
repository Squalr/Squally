#include "FireAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireAxePlans::SaveKeyFireAxePlans = "fire-axe-plans";

FireAxePlans* FireAxePlans::create()
{
	FireAxePlans* instance = new FireAxePlans();

	instance->autorelease();

	return instance;
}

FireAxePlans::FireAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

FireAxePlans::~FireAxePlans()
{
}

Item* FireAxePlans::craft()
{
	return FireAxe::create();
}

std::vector<std::tuple<Item*, int>> FireAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* FireAxePlans::clone()
{
	return FireAxePlans::create();
}

std::string FireAxePlans::getItemName()
{
	return FireAxePlans::SaveKeyFireAxePlans;
}

LocalizedString* FireAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_FireAxe::create();
}

std::string FireAxePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string FireAxePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_FireAxe;
}

std::string FireAxePlans::getSerializationKey()
{
	return FireAxePlans::SaveKeyFireAxePlans;
}
