#include "CopperHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperHelm::SaveKey = "copper-helm";

CopperHelm* CopperHelm::create()
{
	CopperHelm* instance = new CopperHelm();

	instance->autorelease();

	return instance;
}

CopperHelm::CopperHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	3,
	// Speed
	0.05f
))
{
}

CopperHelm::~CopperHelm()
{
}

Item* CopperHelm::clone()
{
	return CopperHelm::create();
}

std::string CopperHelm::getItemName()
{
	return CopperHelm::SaveKey;
}

LocalizedString* CopperHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_CopperHelm::create();
}

std::string CopperHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_CopperHelm;
}

std::string CopperHelm::getSerializationKey()
{
	return CopperHelm::SaveKey;
}

Vec2 CopperHelm::getDisplayOffset()
{
	return Vec2(10.0f, -2.0f);
}
