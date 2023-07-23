#include "Clover.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Clover::SaveKey = "clover";

Clover* Clover::create()
{
	Clover* instance = new Clover();

	instance->autorelease();

	return instance;
}

Clover::Clover() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(20000))
{
}

Clover::~Clover()
{
}

Item* Clover::clone()
{
	return Clover::create();
}

LocalizedString* Clover::getString()
{
	return Strings::Items_Crafting_PotionReagents_Clover::create();
}

const std::string& Clover::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Potions_T1_Clover;
}

const std::string& Clover::getIdentifier()
{
	return Clover::SaveKey;
}
