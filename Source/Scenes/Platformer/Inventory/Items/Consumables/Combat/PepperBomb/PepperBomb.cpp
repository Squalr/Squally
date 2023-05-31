#include "PepperBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/PepperBomb/ThrowPepperBomb.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PepperBomb::SaveKey = "pepper-bomb";
const int PepperBomb::DamageMin = 40;
const int PepperBomb::DamageMax = 44;

PepperBomb* PepperBomb::create()
{
	PepperBomb* instance = new PepperBomb();

	instance->autorelease();

	return instance;
}

PepperBomb::PepperBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 44 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

PepperBomb::~PepperBomb()
{
}

bool PepperBomb::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

LocalizedString* PepperBomb::getDescription()
{
	return Strings::Items_Consumables_Combat_BombDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(PepperBomb::DamageMin)),
			ConstantString::create(std::to_string(PepperBomb::DamageMax))
		});
}

Item* PepperBomb::clone()
{
	return PepperBomb::create();
}

LocalizedString* PepperBomb::getString()
{
	return Strings::Items_Consumables_Combat_PepperBomb::create();
}

const std::string& PepperBomb::getIconResource()
{
	return ItemResources::Consumables_Combat_T4_PepperBomb;
}

const std::string& PepperBomb::getIdentifier()
{
	return PepperBomb::SaveKey;
}

PlatformerAttack* PepperBomb::createAssociatedAttack()
{
	return ThrowPepperBomb::create(PlatformerAttack::Priority::Common);
}
