#include "GrimManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimEqBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GrimManaBehavior::MapKey = "grim-mana";

GrimManaBehavior* GrimManaBehavior::create(GameObject* owner)
{
	GrimManaBehavior* instance = new GrimManaBehavior(owner);

	instance->autorelease();

	return instance;
}

GrimManaBehavior::GrimManaBehavior(GameObject* owner) : super(owner)
{
	this->grim = dynamic_cast<Grim*>(owner);

	if (this->grim == nullptr)
	{
		this->invalidate();
	}
}

GrimManaBehavior::~GrimManaBehavior()
{
}

void GrimManaBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));
	
	this->grim->watchForComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		// Hacky fix -- this data needs to be available to calculate max MP properly. Solving the data race would be a difficult refactor, not worth it.
		this->grim->setState(StateKeys::Eq, SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGrimEq, Value(GrimEqBehavior::DefaultLevel)));
		this->grim->setState(StateKeys::EqExperience, SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGrimEqExperience, Value(0)));

		int mana = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGrimMana, Value(manaBehavior->getMaxMana())).asInt();

		manaBehavior->setMana(mana);
	});

	this->grim->listenForStateWrite(StateKeys::Mana, [=](Value value)
	{
		this->saveState();
	});
}

void GrimManaBehavior::onDisable()
{
	super::onDisable();
}

void GrimManaBehavior::saveState()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGrimMana, this->grim->getRuntimeStateOrDefault(StateKeys::Mana, Value(0)));
}
