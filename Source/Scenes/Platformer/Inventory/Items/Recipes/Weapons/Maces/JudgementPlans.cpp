#include "JudgementPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string JudgementPlans::SaveKeyJudgementPlans = "judgement-plans";

JudgementPlans* JudgementPlans::create()
{
	JudgementPlans* instance = new JudgementPlans();

	instance->autorelease();

	return instance;
}

JudgementPlans::JudgementPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

JudgementPlans::~JudgementPlans()
{
}

Item* JudgementPlans::craft()
{
	return Judgement::create();
}

std::vector<std::tuple<Item*, int>> JudgementPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 6 },
		{ Coal::create(), 6 },
		{ Gold::create(), 4 },
		{ Silver::create(), 2 },
	};
}

Item* JudgementPlans::clone()
{
	return JudgementPlans::create();
}

std::string JudgementPlans::getItemName()
{
	return JudgementPlans::SaveKeyJudgementPlans;
}

LocalizedString* JudgementPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_Judgement::create();
}

std::string JudgementPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string JudgementPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_Judgement;
}

std::string JudgementPlans::getSerializationKey()
{
	return JudgementPlans::SaveKeyJudgementPlans;
}
