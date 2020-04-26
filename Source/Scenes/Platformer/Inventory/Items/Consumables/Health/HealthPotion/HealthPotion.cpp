#include "HealthPotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion/ThrowHealthPotion.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HealthPotion::SaveKey = "health-potion";
const float HealthPotion::HealPercentage = 0.75f;

HealthPotion* HealthPotion::create()
{
	HealthPotion* instance = new HealthPotion();

	instance->autorelease();

	return instance;
}

HealthPotion::HealthPotion() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 14 }}), ItemMeta(20, RubberBanding(3, 0.15f)), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->addChild(this->outOfCombatSound);
}

HealthPotion::~HealthPotion()
{
}

void HealthPotion::useOutOfCombat(PlatformerEntity* target)
{
	target->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->setHealth(healthBehavior->getHealth() + int(float(healthBehavior->getMaxHealth()) * HealthPotion::HealPercentage));
	});

	this->outOfCombatSound->play();
}

bool HealthPotion::canUseOnTarget(PlatformerEntity* target)
{
	if (!target->getStateOrDefaultBool(StateKeys::IsAlive, true))
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

Item* HealthPotion::clone()
{
	return HealthPotion::create();
}

std::string HealthPotion::getItemName()
{
	return HealthPotion::SaveKey;
}

LocalizedString* HealthPotion::getString()
{
	return Strings::Items_Consumables_Health_HealthPotion::create();
}

std::string HealthPotion::getIconResource()
{
	return ItemResources::Consumables_Potions_HealthPotion;
}

std::string HealthPotion::getSerializationKey()
{
	return HealthPotion::SaveKey;
}

PlatformerAttack* HealthPotion::createAssociatedAttack()
{
	return ThrowHealthPotion::create(PlatformerAttack::Priority::Common, HealthPotion::HealPercentage, this->getIconResource());
}
