#include "GeckyHealthBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GeckyHealthBehavior::MapKey = "gecky-health";

GeckyHealthBehavior* GeckyHealthBehavior::create(GameObject* owner)
{
	GeckyHealthBehavior* instance = new GeckyHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

GeckyHealthBehavior::GeckyHealthBehavior(GameObject* owner) : super(owner)
{
	this->guano = dynamic_cast<Gecky*>(owner);

	if (this->guano == nullptr)
	{
		this->invalidate();
	}
}

GeckyHealthBehavior::~GeckyHealthBehavior()
{
}

void GeckyHealthBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));
	
	this->guano->watchForAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		int health = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGeckyHealth, Value(healthBehavior->getMaxHealth())).asInt();

		healthBehavior->setHealth(health);
	});

	this->guano->listenForStateWrite(StateKeys::Health, [=](Value value)
	{
		this->saveState();
	});
}

void GeckyHealthBehavior::onDisable()
{
	super::onDisable();
}

void GeckyHealthBehavior::saveState()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGeckyHealth, this->guano->getRuntimeStateOrDefault(StateKeys::Health, Value(0)));
}
