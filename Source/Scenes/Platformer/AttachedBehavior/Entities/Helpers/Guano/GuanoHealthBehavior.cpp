#include "GuanoHealthBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
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

const std::string GuanoHealthBehavior::MapKey = "guano-health";

GuanoHealthBehavior* GuanoHealthBehavior::create(GameObject* owner)
{
	GuanoHealthBehavior* instance = new GuanoHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoHealthBehavior::GuanoHealthBehavior(GameObject* owner) : super(owner)
{
	this->guano = dynamic_cast<Guano*>(owner);

	if (this->guano == nullptr)
	{
		this->invalidate();
	}
}

GuanoHealthBehavior::~GuanoHealthBehavior()
{
}

void GuanoHealthBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));
	
	this->guano->watchForAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		int health = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGuanoHealth, Value(healthBehavior->getMaxHealth())).asInt();

		healthBehavior->setHealth(health);
	});

	this->guano->listenForStateWrite(StateKeys::Health, [=](Value value)
	{
		this->saveState();
	});
}

void GuanoHealthBehavior::onDisable()
{
	super::onDisable();
}

void GuanoHealthBehavior::saveState()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGuanoHealth, this->guano->getRuntimeStateOrDefault(StateKeys::Health, Value(0)));
}
