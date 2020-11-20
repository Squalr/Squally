#include "GeckyManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GeckyManaBehavior::MapKey = "gecky-mana";

GeckyManaBehavior* GeckyManaBehavior::create(GameObject* owner)
{
	GeckyManaBehavior* instance = new GeckyManaBehavior(owner);

	instance->autorelease();

	return instance;
}

GeckyManaBehavior::GeckyManaBehavior(GameObject* owner) : super(owner)
{
	this->guano = dynamic_cast<Gecky*>(owner);

	if (this->guano == nullptr)
	{
		this->invalidate();
	}
}

GeckyManaBehavior::~GeckyManaBehavior()
{
}

void GeckyManaBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));
	
	this->guano->watchForAttachedBehavior<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		int mana = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGeckyMana, Value(manaBehavior->getMaxMana())).asInt();

		manaBehavior->setMana(mana);
	});

	this->guano->listenForStateWrite(StateKeys::Mana, [=](Value value)
	{
		this->saveState();
	});
}

void GeckyManaBehavior::onDisable()
{
	super::onDisable();
}

void GeckyManaBehavior::saveState()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGeckyMana, this->guano->getRuntimeStateOrDefault(StateKeys::Mana, Value(0)));
}
