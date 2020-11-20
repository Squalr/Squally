#include "GuanoManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GuanoManaBehavior::MapKey = "guano-mana";

GuanoManaBehavior* GuanoManaBehavior::create(GameObject* owner)
{
	GuanoManaBehavior* instance = new GuanoManaBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoManaBehavior::GuanoManaBehavior(GameObject* owner) : super(owner)
{
	this->guano = dynamic_cast<Guano*>(owner);

	if (this->guano == nullptr)
	{
		this->invalidate();
	}
}

GuanoManaBehavior::~GuanoManaBehavior()
{
}

void GuanoManaBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));
	
	this->guano->watchForAttachedBehavior<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		int mana = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGuanoMana, Value(manaBehavior->getMaxMana())).asInt();

		manaBehavior->setMana(mana);
	});

	this->guano->listenForStateWrite(StateKeys::Mana, [=](Value value)
	{
		this->saveState();
	});
}

void GuanoManaBehavior::onDisable()
{
	super::onDisable();
}

void GuanoManaBehavior::saveState()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGuanoMana, this->guano->getRuntimeStateOrDefault(StateKeys::Mana, Value(0)));
}
