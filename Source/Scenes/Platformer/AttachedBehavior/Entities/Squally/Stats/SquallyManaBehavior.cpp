#include "SquallyManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyManaBehavior::MapKeyAttachedBehavior = "squally-mana";

SquallyManaBehavior* SquallyManaBehavior::create(GameObject* owner)
{
	SquallyManaBehavior* instance = new SquallyManaBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyManaBehavior::SquallyManaBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyManaBehavior::~SquallyManaBehavior()
{
}

void SquallyManaBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));
	
	this->defer([=]()
	{
		this->squally->watchForAttachedBehavior<EntityManaBehavior>([=](EntityManaBehavior* entityManaBehavior)
		{
			this->recalculateMaxMana([=]()
			{
				int mana = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(777)).asInt();

				this->squally->setState(StateKeys::Mana, Value(mana));
			});
		});
	});
}

void SquallyManaBehavior::onDisable()
{
	super::onDisable();
}

void SquallyManaBehavior::saveState()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyMana, this->squally->getStateOrDefault(StateKeys::Mana, Value(0)));
}

void SquallyManaBehavior::recalculateMaxMana(std::function<void()> onCalculated)
{
	this->squally->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		int maxMana = StatsTables::getBaseMana(this->squally);

		for (auto item : entityInventoryBehavior->getEquipmentInventory()->getEquipment())
		{
			maxMana += item->getItemStats().manaBonus;
		}

		this->squally->setState(StateKeys::MaxMana, Value(maxMana));

		onCalculated();
	});
}

