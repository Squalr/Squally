#include "SuperiorManaFlask.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/SuperiorManaFlask/ThrowSuperiorManaFlask.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SuperiorManaFlask::SaveKey = "superior-mana-flask";
const float SuperiorManaFlask::RestorePercentage = 0.8f;

SuperiorManaFlask* SuperiorManaFlask::create()
{
	SuperiorManaFlask* instance = new SuperiorManaFlask();

	instance->autorelease();

	return instance;
}

SuperiorManaFlask::SuperiorManaFlask() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 43 }}), ItemMeta(20, RubberBanding(3, 0.15f)), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->outOfCombatSound->toggleIgnorePause(true);

	this->addChild(this->outOfCombatSound);
}

SuperiorManaFlask::~SuperiorManaFlask()
{
}

void SuperiorManaFlask::useOutOfCombat(PlatformerEntity* target)
{
	target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		manaBehavior->setMana(manaBehavior->getMana() + int(float(manaBehavior->getMaxMana()) * SuperiorManaFlask::RestorePercentage));
	});

	this->outOfCombatSound->play();
}

bool SuperiorManaFlask::canUseOnTarget(PlatformerEntity* target)
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

LocalizedString* SuperiorManaFlask::getDescription()
{
	return Strings::Items_Consumables_Mana_SuperiorManaFlaskDescription::create()
		->setStringReplacementVariables(ConstantString::create(std::to_string(int(SuperiorManaFlask::RestorePercentage * 100.0f))));
}

Item* SuperiorManaFlask::clone()
{
	return SuperiorManaFlask::create();
}

LocalizedString* SuperiorManaFlask::getString()
{
	return Strings::Items_Consumables_Mana_SuperiorManaFlask::create();
}

const std::string& SuperiorManaFlask::getIconResource()
{
	return ItemResources::Consumables_Potions_ManaFlaskSuperior;
}

const std::string& SuperiorManaFlask::getIdentifier()
{
	return SuperiorManaFlask::SaveKey;
}

PlatformerAttack* SuperiorManaFlask::createAssociatedAttack()
{
	return ThrowSuperiorManaFlask::create(PlatformerAttack::Priority::Common);
}
