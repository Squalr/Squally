#include "GoldenDungHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenDungHelm::SaveKey = "golden-dung-helm";

GoldenDungHelm* GoldenDungHelm::create()
{
	GoldenDungHelm* instance = new GoldenDungHelm();

	instance->autorelease();

	return instance;
}

GoldenDungHelm::GoldenDungHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

GoldenDungHelm::~GoldenDungHelm()
{
}

Item* GoldenDungHelm::clone()
{
	return GoldenDungHelm::create();
}

const std::string& GoldenDungHelm::getItemName()
{
	return GoldenDungHelm::SaveKey;
}

LocalizedString* GoldenDungHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GoldenDungHelm::create();
}

const std::string& GoldenDungHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GoldenDungHelm;
}

const std::string& GoldenDungHelm::getIdentifier()
{
	return GoldenDungHelm::SaveKey;
}

Vec2 GoldenDungHelm::getDisplayOffset()
{
	return Vec2(8.0f, 26.0f);
}
