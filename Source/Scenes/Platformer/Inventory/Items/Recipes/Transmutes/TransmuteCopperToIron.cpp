#include "TransmuteCopperToIron.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TransmuteCopperToIron::SaveKey = "copper-to-iron-recipe";

TransmuteCopperToIron* TransmuteCopperToIron::create()
{
	TransmuteCopperToIron* instance = new TransmuteCopperToIron();

	instance->autorelease();

	return instance;
}

TransmuteCopperToIron::TransmuteCopperToIron() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TransmuteCopperToIron::~TransmuteCopperToIron()
{
}

std::vector<Item*> TransmuteCopperToIron::craft()
{
	return { Iron::create() };
}

std::vector<std::tuple<Item*, int>> TransmuteCopperToIron::getReagentsInternal()
{
	return
	{
		{ Copper::create(), 4 },
		{ Coal::create(), 1 },
	};
}

Item* TransmuteCopperToIron::clone()
{
	return TransmuteCopperToIron::create();
}

LocalizedString* TransmuteCopperToIron::getString()
{
	return Strings::Items_Crafting_Recipes_TransmuteGeneric::create()->setStringReplacementVariables({
		Strings::Items_Crafting_Ore_Copper::create(),
		Strings::Items_Crafting_Ore_Iron::create()
	});
}

const std::string& TransmuteCopperToIron::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TransmuteCopperToIron::getCraftedItemIconResource()
{
	return ItemResources::Crafting_Smithing_T2_Iron;
}

const std::string& TransmuteCopperToIron::getIdentifier()
{
	return TransmuteCopperToIron::SaveKey;
}
