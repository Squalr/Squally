#include "Acorn.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Acorn::SaveKey = "acorn";

Acorn* Acorn::create()
{
	Acorn* instance = new Acorn();

	instance->autorelease();

	return instance;
}

Acorn::Acorn() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), ItemMeta(20000))
{
}

Acorn::~Acorn()
{
}

Item* Acorn::clone()
{
	return Acorn::create();
}

LocalizedString* Acorn::getString()
{
	return Strings::Items_Crafting_PotionReagents_Acorn::create();
}

const std::string& Acorn::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Potions_T2_Acorn;
}

const std::string& Acorn::getIdentifier()
{
	return Acorn::SaveKey;
}
