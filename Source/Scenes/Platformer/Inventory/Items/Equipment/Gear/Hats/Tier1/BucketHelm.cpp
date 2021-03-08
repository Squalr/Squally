#include "BucketHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BucketHelm::SaveKey = "bucket-helm";

BucketHelm* BucketHelm::create()
{
	BucketHelm* instance = new BucketHelm();

	instance->autorelease();

	return instance;
}

BucketHelm::BucketHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 8 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	1,
	// Speed
	0.05f
))
{
}

BucketHelm::~BucketHelm()
{
}

Item* BucketHelm::clone()
{
	return BucketHelm::create();
}

const std::string& BucketHelm::getItemName()
{
	return BucketHelm::SaveKey;
}

LocalizedString* BucketHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_BucketHelm::create();
}

const std::string& BucketHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_BucketHelm;
}

const std::string& BucketHelm::getSerializationKey()
{
	return BucketHelm::SaveKey;
}

Vec2 BucketHelm::getDisplayOffset()
{
	return Vec2(6.0f, -20.0f);
}
