#include "Judgement.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/Judgement.h"

using namespace cocos2d;

const std::string Judgement::SaveKeyJudgement = "judgement";

Judgement* Judgement::create()
{
	Judgement* instance = new Judgement();

	instance->autorelease();

	return instance;
}

Judgement::Judgement() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

Judgement::~Judgement()
{
}

Item* Judgement::clone()
{
	return Judgement::create();
}

std::string Judgement::getItemName()
{
	return Judgement::SaveKeyJudgement;
}

LocalizedString* Judgement::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_Judgement::create();
}

std::string Judgement::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_Judgement;
}

std::string Judgement::getSerializationKey()
{
	return Judgement::SaveKeyJudgement;
}

Vec2 Judgement::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
