#include "FragGrenade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/FragGrenade/ThrowFragGrenade.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FragGrenade::SaveKey = "frag-grenade";
const int FragGrenade::DamageMin = 60;
const int FragGrenade::DamageMax = 64;

FragGrenade* FragGrenade::create()
{
	FragGrenade* instance = new FragGrenade();

	instance->autorelease();

	return instance;
}

FragGrenade::FragGrenade() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 64 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

FragGrenade::~FragGrenade()
{
}

bool FragGrenade::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

Item* FragGrenade::clone()
{
	return FragGrenade::create();
}

LocalizedString* FragGrenade::getDescription()
{
	return Strings::Items_Consumables_Combat_BombDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(FragGrenade::DamageMin)),
			ConstantString::create(std::to_string(FragGrenade::DamageMax))
		});
}

LocalizedString* FragGrenade::getString()
{
	return Strings::Items_Consumables_Combat_FragGrenade::create();
}

const std::string& FragGrenade::getIconResource()
{
	return ItemResources::Consumables_Combat_T6_FragGrenade;
}

const std::string& FragGrenade::getIdentifier()
{
	return FragGrenade::SaveKey;
}

PlatformerAttack* FragGrenade::createAssociatedAttack()
{
	return ThrowFragGrenade::create(PlatformerAttack::Priority::Common);
}
