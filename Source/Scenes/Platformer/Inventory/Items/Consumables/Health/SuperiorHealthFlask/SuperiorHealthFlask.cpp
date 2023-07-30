#include "SuperiorHealthFlask.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/SuperiorHealthFlask/ThrowSuperiorHealthFlask.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SuperiorHealthFlask::SaveKey = "superior-health-flask";
const int SuperiorHealthFlask::HealTicks = 4;

SuperiorHealthFlask* SuperiorHealthFlask::create()
{
	SuperiorHealthFlask* instance = new SuperiorHealthFlask();

	instance->autorelease();

	return instance;
}

SuperiorHealthFlask::SuperiorHealthFlask() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20, RubberBanding(3, 0.15f)), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->outOfCombatSound->toggleIgnorePause(true);

	this->addChild(this->outOfCombatSound);
}

SuperiorHealthFlask::~SuperiorHealthFlask()
{
}

void SuperiorHealthFlask::useOutOfCombat(PlatformerEntity* target)
{
	target->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->setHealth(healthBehavior->getHealth() + SuperiorHealthFlask::HealTicks);
	});

	this->outOfCombatSound->play();
}

bool SuperiorHealthFlask::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	bool canUse = true;

	target->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
	{
		if (healthBehavior->getHealth() == healthBehavior->getMaxHealth())
		{
			canUse = false;
		}
	});
	
	return canUse;
}

LocalizedString* SuperiorHealthFlask::getDescription()
{
	return Strings::Items_Consumables_Health_SuperiorHealthFlaskDescription::create()
		->setStringReplacementVariables({ ConstantString::create(std::to_string(int(SuperiorHealthFlask::HealTicks))), ConstantString::create(std::to_string(int(SuperiorHealthFlask::HealTicks))) });
}

Item* SuperiorHealthFlask::clone()
{
	return SuperiorHealthFlask::create();
}

LocalizedString* SuperiorHealthFlask::getString()
{
	return Strings::Items_Consumables_Health_SuperiorHealthFlask::create();
}

const std::string& SuperiorHealthFlask::getIconResource()
{
	return ItemResources::Consumables_Potions_HealthFlaskSuperior;
}

const std::string& SuperiorHealthFlask::getIdentifier()
{
	return SuperiorHealthFlask::SaveKey;
}

PlatformerAttack* SuperiorHealthFlask::createAssociatedAttack()
{
	return ThrowSuperiorHealthFlask::create(PlatformerAttack::Priority::Common);
}
