#include "GreaterManaPotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/GreaterManaPotion/ThrowGreaterManaPotion.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GreaterManaPotion::SaveKey = "greater-mana-potion";
const float GreaterManaPotion::RestorePercentage = 0.6f;

GreaterManaPotion* GreaterManaPotion::create()
{
	GreaterManaPotion* instance = new GreaterManaPotion();

	instance->autorelease();

	return instance;
}

GreaterManaPotion::GreaterManaPotion() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 30 }}), ItemMeta(20, RubberBanding(3, 0.15f)), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->addChild(this->outOfCombatSound);
}

GreaterManaPotion::~GreaterManaPotion()
{
}

void GreaterManaPotion::useOutOfCombat(PlatformerEntity* target)
{
	target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		manaBehavior->setMana(manaBehavior->getMana() + int(float(manaBehavior->getMaxMana()) * GreaterManaPotion::RestorePercentage));
	});

	this->outOfCombatSound->play();
}

bool GreaterManaPotion::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	bool canUse = true;

	target->getComponent<EntityManaBehavior>([&](EntityManaBehavior* manaBehavior)
	{
		if (manaBehavior->getMana() == manaBehavior->getMaxMana())
		{
			canUse = false;
		}
	});
	
	return canUse;
}

LocalizedString* GreaterManaPotion::getDescription()
{
	return Strings::Items_Consumables_Mana_GreaterManaPotionDescription::create()
		->setStringReplacementVariables(ConstantString::create(std::to_string(int(GreaterManaPotion::RestorePercentage * 100.0f))));
}

Item* GreaterManaPotion::clone()
{
	return GreaterManaPotion::create();
}

LocalizedString* GreaterManaPotion::getString()
{
	return Strings::Items_Consumables_Mana_GreaterManaPotion::create();
}

const std::string& GreaterManaPotion::getIconResource()
{
	return ItemResources::Consumables_Potions_ManaPotionGreater;
}

const std::string& GreaterManaPotion::getIdentifier()
{
	return GreaterManaPotion::SaveKey;
}

PlatformerAttack* GreaterManaPotion::createAssociatedAttack()
{
	return ThrowGreaterManaPotion::create(PlatformerAttack::Priority::Common);
}
