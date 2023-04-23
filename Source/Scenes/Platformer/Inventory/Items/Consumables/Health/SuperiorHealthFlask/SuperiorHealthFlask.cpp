#include "SuperiorHealthFlask.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion/ThrowHealthPotion.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SuperiorHealthFlask::SaveKey = "superior-health-flask";
const float SuperiorHealthFlask::HealPercentage = 1.0f;

SuperiorHealthFlask* SuperiorHealthFlask::create()
{
	SuperiorHealthFlask* instance = new SuperiorHealthFlask();

	instance->autorelease();

	return instance;
}

// Note: No rubber-banding, as these are to be considered a rare item
SuperiorHealthFlask::SuperiorHealthFlask() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 45 }}), ItemMeta(20), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->addChild(this->outOfCombatSound);
}

SuperiorHealthFlask::~SuperiorHealthFlask()
{
}

void SuperiorHealthFlask::useOutOfCombat(PlatformerEntity* target)
{
	target->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->setHealth(healthBehavior->getHealth() + int(float(healthBehavior->getMaxHealth()) * SuperiorHealthFlask::HealPercentage));
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
	return ThrowHealthPotion::create(PlatformerAttack::Priority::Common);
}
