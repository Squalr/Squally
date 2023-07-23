#include "SpikedBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/SpikedBomb/ThrowSpikedBomb.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpikedBomb::SaveKey = "spiked-bomb";
const int SpikedBomb::DamageMin = 50;
const int SpikedBomb::DamageMax = 54;

SpikedBomb* SpikedBomb::create()
{
	SpikedBomb* instance = new SpikedBomb();

	instance->autorelease();

	return instance;
}

SpikedBomb::SpikedBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 54 }}), ItemMeta(20, RubberBanding(3, 0.15f)), false)
{
}

SpikedBomb::~SpikedBomb()
{
}

bool SpikedBomb::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	return true;
}

LocalizedString* SpikedBomb::getDescription()
{
	return Strings::Items_Consumables_Combat_BombDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(SpikedBomb::DamageMin)),
			ConstantString::create(std::to_string(SpikedBomb::DamageMax))
		});
}

Item* SpikedBomb::clone()
{
	return SpikedBomb::create();
}

LocalizedString* SpikedBomb::getString()
{
	return Strings::Items_Consumables_Combat_SpikedBomb::create();
}

const std::string& SpikedBomb::getIconResource()
{
	return ItemResources::Consumables_Combat_T5_SpikedBomb;
}

const std::string& SpikedBomb::getIdentifier()
{
	return SpikedBomb::SaveKey;
}

PlatformerAttack* SpikedBomb::createAssociatedAttack()
{
	return ThrowSpikedBomb::create(PlatformerAttack::Priority::Common);
}
