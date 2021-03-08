#include "BlackBlood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BlackBlood::SaveKey = "black-blood";

BlackBlood* BlackBlood::create()
{
	BlackBlood* instance = new BlackBlood();

	instance->autorelease();

	return instance;
}

BlackBlood::BlackBlood() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 18 }}), ItemMeta(20000))
{
}

BlackBlood::~BlackBlood()
{
}

Item* BlackBlood::clone()
{
	return BlackBlood::create();
}

const std::string& BlackBlood::getItemName()
{
	return BlackBlood::SaveKey;
}

LocalizedString* BlackBlood::getString()
{
	return Strings::Items_Crafting_Reagents_BlackBlood::create();
}

const std::string& BlackBlood::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Reagents_BlackBlood;
}

const std::string& BlackBlood::getSerializationKey()
{
	return BlackBlood::SaveKey;
}
