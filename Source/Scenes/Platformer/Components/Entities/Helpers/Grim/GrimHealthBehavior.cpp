#include "GrimHealthBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimEqBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GrimHealthBehavior::MapKey = "grim-health";

GrimHealthBehavior* GrimHealthBehavior::create(GameObject* owner)
{
	GrimHealthBehavior* instance = new GrimHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

GrimHealthBehavior::GrimHealthBehavior(GameObject* owner) : super(owner)
{
	this->grim = dynamic_cast<Grim*>(owner);

	if (this->grim == nullptr)
	{
		this->invalidate();
	}
}

GrimHealthBehavior::~GrimHealthBehavior()
{
}

void GrimHealthBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));
	
	this->grim->watchForComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		// Hacky fix -- this data needs to be available to calculate max HP properly. Solving the data race would be a difficult refactor, not worth it.
		this->grim->setState(StateKeys::Eq, SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGrimEq, Value(GrimEqBehavior::DefaultLevel)));
		this->grim->setState(StateKeys::EqExperience, SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGrimEqExperience, Value(0)));

		int health = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGrimHealth, Value(healthBehavior->getMaxHealth())).asInt();

		healthBehavior->setHealth(health);

		this->grim->listenForStateWrite(StateKeys::Health, [=](Value value)
		{
			this->saveState();
		});
	});
}

void GrimHealthBehavior::onDisable()
{
	super::onDisable();
}

void GrimHealthBehavior::saveState()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGrimHealth, this->grim->getRuntimeStateOrDefault(StateKeys::Health, Value(0)));
}
