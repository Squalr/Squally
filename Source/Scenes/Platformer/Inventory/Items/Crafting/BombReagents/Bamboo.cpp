#include "Bamboo.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bamboo::SaveKey = "bamboo";

Bamboo* Bamboo::create()
{
	Bamboo* instance = new Bamboo();

	instance->autorelease();

	return instance;
}

Bamboo::Bamboo() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 43 }}), ItemMeta(20000))
{
}

Bamboo::~Bamboo()
{
}

Item* Bamboo::clone()
{
	return Bamboo::create();
}

LocalizedString* Bamboo::getString()
{
	return Strings::Items_Crafting_BombReagents_Bamboo::create();
}

const std::string& Bamboo::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T1_Bamboo;
}

const std::string& Bamboo::getIdentifier()
{
	return Bamboo::SaveKey;
}
