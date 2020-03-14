#include "VikingSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VikingSwordPlans::SaveKeyVikingSwordPlans = "viking-sword-plans";

VikingSwordPlans* VikingSwordPlans::create()
{
	VikingSwordPlans* instance = new VikingSwordPlans();

	instance->autorelease();

	return instance;
}

VikingSwordPlans::VikingSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

VikingSwordPlans::~VikingSwordPlans()
{
}

Item* VikingSwordPlans::craft()
{
	return VikingSword::create();
}

std::vector<std::tuple<Item*, int>> VikingSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 1 },
		{ Iron::create(), 8 },
		{ Coal::create(), 2 },
	};
}

Item* VikingSwordPlans::clone()
{
	return VikingSwordPlans::create();
}

std::string VikingSwordPlans::getItemName()
{
	return VikingSwordPlans::SaveKeyVikingSwordPlans;
}

LocalizedString* VikingSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_VikingSword::create();
}

std::string VikingSwordPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string VikingSwordPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_VikingSword;
}

std::string VikingSwordPlans::getSerializationKey()
{
	return VikingSwordPlans::SaveKeyVikingSwordPlans;
}
