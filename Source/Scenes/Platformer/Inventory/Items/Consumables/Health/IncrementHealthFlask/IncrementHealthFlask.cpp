#include "IncrementHealthFlask.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/ThrowIncrementHealthFlask.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IncrementHealthFlask::SaveKey = "increment-health-flask";
const int IncrementHealthFlask::HealTicks = 8;

IncrementHealthFlask* IncrementHealthFlask::create()
{
	IncrementHealthFlask* instance = new IncrementHealthFlask();

	instance->autorelease();

	return instance;
}

IncrementHealthFlask::IncrementHealthFlask() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20, RubberBanding(3, 0.15f)), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->addChild(this->outOfCombatSound);
}

IncrementHealthFlask::~IncrementHealthFlask()
{
}

void IncrementHealthFlask::useOutOfCombat(PlatformerEntity* target)
{
	target->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->setHealth(healthBehavior->getHealth() + IncrementHealthFlask::HealTicks);
	});

	this->outOfCombatSound->play();
}

bool IncrementHealthFlask::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return false;
	}
	
	bool canUse = true;

	target->getAttachedBehavior<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
	{
		if (healthBehavior->getHealth() == healthBehavior->getMaxHealth())
		{
			canUse = false;
		}
	});
	
	return canUse;
}

Item* IncrementHealthFlask::clone()
{
	return IncrementHealthFlask::create();
}

const std::string& IncrementHealthFlask::getItemName()
{
	return IncrementHealthFlask::SaveKey;
}

LocalizedString* IncrementHealthFlask::getString()
{
	return Strings::Items_Consumables_Health_IncrementHealthFlask::create();
}

const std::string& IncrementHealthFlask::getIconResource()
{
	return ItemResources::Consumables_Potions_HealthFlaskIncrement;
}

const std::string& IncrementHealthFlask::getIdentifier()
{
	return IncrementHealthFlask::SaveKey;
}

PlatformerAttack* IncrementHealthFlask::createAssociatedAttack()
{
	return ThrowIncrementHealthFlask::create(PlatformerAttack::Priority::Common);
}
