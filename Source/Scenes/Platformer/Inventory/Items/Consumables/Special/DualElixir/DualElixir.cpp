#include "DualElixir.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Special/DualElixir/ThrowDualElixir.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DualElixir::SaveKey = "dual-elixir";
const float DualElixir::RestoreHealthPercentage = 0.75f;
const float DualElixir::RestoreManaPercentage = 0.75f;

DualElixir* DualElixir::create()
{
	DualElixir* instance = new DualElixir();

	instance->autorelease();

	return instance;
}

DualElixir::DualElixir() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 43 }}), ItemMeta(20, RubberBanding(3, 0.15f)), true)
{
	this->outOfCombatSound = Sound::create(SoundResources::Platformer_FX_Potions_PotionDrink2);

	this->addChild(this->outOfCombatSound);
}

DualElixir::~DualElixir()
{
}

void DualElixir::useOutOfCombat(PlatformerEntity* target)
{
	target->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->setHealth(healthBehavior->getHealth() + int(float(healthBehavior->getMaxHealth()) * DualElixir::RestoreHealthPercentage));
	});

	target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		manaBehavior->setMana(manaBehavior->getMana() + int(float(manaBehavior->getMaxMana()) * DualElixir::RestoreManaPercentage));
	});

	this->outOfCombatSound->play();
}

bool DualElixir::canUseOnTarget(PlatformerEntity* target)
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

LocalizedString* DualElixir::getDescription()
{
	return Strings::Items_Consumables_Special_DualElixirDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(int(DualElixir::RestoreHealthPercentage * 100.0f))),
			ConstantString::create(std::to_string(int(DualElixir::RestoreManaPercentage * 100.0f)))
		});
}

Item* DualElixir::clone()
{
	return DualElixir::create();
}

LocalizedString* DualElixir::getString()
{
	return Strings::Items_Consumables_Special_DualElixir::create();
}

const std::string& DualElixir::getIconResource()
{
	return ItemResources::Consumables_Potions_DualElixir;
}

const std::string& DualElixir::getIdentifier()
{
	return DualElixir::SaveKey;
}

PlatformerAttack* DualElixir::createAssociatedAttack()
{
	return ThrowDualElixir::create(PlatformerAttack::Priority::Common);
}
