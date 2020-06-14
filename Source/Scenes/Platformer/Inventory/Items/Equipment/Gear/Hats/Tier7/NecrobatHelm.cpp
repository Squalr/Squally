#include "NecrobatHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string NecrobatHelm::SaveKey = "necrobat-helm";

NecrobatHelm* NecrobatHelm::create()
{
	NecrobatHelm* instance = new NecrobatHelm();

	instance->autorelease();

	return instance;
}

NecrobatHelm::NecrobatHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

NecrobatHelm::~NecrobatHelm()
{
}

Item* NecrobatHelm::clone()
{
	return NecrobatHelm::create();
}

std::string NecrobatHelm::getItemName()
{
	return NecrobatHelm::SaveKey;
}

LocalizedString* NecrobatHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_NecrobatHelm::create();
}

std::string NecrobatHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_NecrobatHelm;
}

std::string NecrobatHelm::getSerializationKey()
{
	return NecrobatHelm::SaveKey;
}

Vec2 NecrobatHelm::getDisplayOffset()
{
	return Vec2(-42.0f, 22.0f);
}
