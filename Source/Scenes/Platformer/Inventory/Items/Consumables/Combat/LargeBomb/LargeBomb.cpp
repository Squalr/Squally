#include "LargeBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/LargeBomb/ThrowLargeBomb.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LargeBomb::SaveKey = "large-bomb";
const int LargeBomb::DamageMin = 30;
const int LargeBomb::DamageMax = 34;

LargeBomb* LargeBomb::create()
{
	LargeBomb* instance = new LargeBomb();

	instance->autorelease();

	return instance;
}

LargeBomb::LargeBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 34 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

LargeBomb::~LargeBomb()
{
}

bool LargeBomb::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

LocalizedString* LargeBomb::getDescription()
{
	return Strings::Items_Consumables_Combat_BombDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(LargeBomb::DamageMin)),
			ConstantString::create(std::to_string(LargeBomb::DamageMax))
		});
}

Item* LargeBomb::clone()
{
	return LargeBomb::create();
}

LocalizedString* LargeBomb::getString()
{
	return Strings::Items_Consumables_Combat_LargeBomb::create();
}

const std::string& LargeBomb::getIconResource()
{
	return ItemResources::Consumables_Combat_T3_LargeBomb;
}

const std::string& LargeBomb::getIdentifier()
{
	return LargeBomb::SaveKey;
}

PlatformerAttack* LargeBomb::createAssociatedAttack()
{
	return ThrowLargeBomb::create(PlatformerAttack::Priority::Common);
}
