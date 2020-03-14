#include "HeadSplitterPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeadSplitterPlans::SaveKeyHeadSplitterPlans = "head-splitter-plans";

HeadSplitterPlans* HeadSplitterPlans::create()
{
	HeadSplitterPlans* instance = new HeadSplitterPlans();

	instance->autorelease();

	return instance;
}

HeadSplitterPlans::HeadSplitterPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HeadSplitterPlans::~HeadSplitterPlans()
{
}

Item* HeadSplitterPlans::craft()
{
	return HeadSplitter::create();
}

std::vector<std::tuple<Item*, int>> HeadSplitterPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* HeadSplitterPlans::clone()
{
	return HeadSplitterPlans::create();
}

std::string HeadSplitterPlans::getItemName()
{
	return HeadSplitterPlans::SaveKeyHeadSplitterPlans;
}

LocalizedString* HeadSplitterPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_HeadSplitter::create();
}

std::string HeadSplitterPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string HeadSplitterPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_HeadSplitter;
}

std::string HeadSplitterPlans::getSerializationKey()
{
	return HeadSplitterPlans::SaveKeyHeadSplitterPlans;
}
