#include "IncrementManaFlask.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/IncrementManaFlask/ThrowIncrementManaFlask.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IncrementManaFlask::SaveKey = "increment-health-flask";
const int IncrementManaFlask::HealTicks = 8;

IncrementManaFlask* IncrementManaFlask::create()
{
	IncrementManaFlask* instance = new IncrementManaFlask();

	instance->autorelease();

	return instance;
}

IncrementManaFlask::IncrementManaFlask() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20, RubberBanding(3, 0.15f)), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->outOfCombatSound->toggleIgnorePause(true);

	this->addChild(this->outOfCombatSound);
}

IncrementManaFlask::~IncrementManaFlask()
{
}

void IncrementManaFlask::useOutOfCombat(PlatformerEntity* target)
{
	target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* healthBehavior)
	{
		healthBehavior->setMana(healthBehavior->getMana() + IncrementManaFlask::HealTicks);
	});

	this->outOfCombatSound->play();
}

bool IncrementManaFlask::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	bool canUse = true;

	target->getComponent<EntityManaBehavior>([&](EntityManaBehavior* healthBehavior)
	{
		if (healthBehavior->getMana() == healthBehavior->getMaxMana())
		{
			canUse = false;
		}
	});
	
	return canUse;
}

LocalizedString* IncrementManaFlask::getDescription()
{
	return Strings::Items_Consumables_Mana_IncrementManaFlaskDescription::create()
		->setStringReplacementVariables({ ConstantString::create(std::to_string(int(IncrementManaFlask::HealTicks))), ConstantString::create(std::to_string(int(IncrementManaFlask::HealTicks))) });
}

Item* IncrementManaFlask::clone()
{
	return IncrementManaFlask::create();
}

LocalizedString* IncrementManaFlask::getString()
{
	return Strings::Items_Consumables_Mana_IncrementManaFlask::create();
}

const std::string& IncrementManaFlask::getIconResource()
{
	return ItemResources::Consumables_Potions_ManaFlaskIncrement;
}

const std::string& IncrementManaFlask::getIdentifier()
{
	return IncrementManaFlask::SaveKey;
}

PlatformerAttack* IncrementManaFlask::createAssociatedAttack()
{
	return ThrowIncrementManaFlask::create(PlatformerAttack::Priority::Common);
}
