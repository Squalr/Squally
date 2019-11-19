#include "ScrappyCombatManagerBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerEntityDeserializer.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/Combat/ScrappyCombatBehaviorGroup.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"


using namespace cocos2d;

const std::string ScrappyCombatManagerBehavior::MapKeyAttachedBehavior = "scrappy-combat-manager";

ScrappyCombatManagerBehavior* ScrappyCombatManagerBehavior::create(GameObject* owner)
{
	ScrappyCombatManagerBehavior* instance = new ScrappyCombatManagerBehavior(owner);

	instance->autorelease();

	return instance;
}

ScrappyCombatManagerBehavior::ScrappyCombatManagerBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->platformerEntityDeserializer = PlatformerEntityDeserializer::create();
	this->helperRef = nullptr;

	this->addChild(this->platformerEntityDeserializer);
}

ScrappyCombatManagerBehavior::~ScrappyCombatManagerBehavior()
{
}

void ScrappyCombatManagerBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforePlatformerMapChange, [=](EventCustom* eventCustom)
	{
		// Since Scrappy is found on the first map, this is a good way to ensure there are no sequence breaks
		SaveManager::softSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
	}));

	this->defer([=]()
	{
		if (SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyScrappyFound, Value(false)).asBool())
		{
			this->spawnScrappy();
		}
	});
}

void ScrappyCombatManagerBehavior::spawnScrappy()
{
	ValueMap properties = ValueMap();

	properties[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
	properties[GameObject::MapKeyName] = Value(Scrappy::MapKeyScrappy);
	properties[GameObject::MapKeyAttachedBehavior] = Value(ScrappyCombatBehaviorGroup::MapKeyAttachedBehavior);
	properties[GameObject::MapKeyFlipX] = Value(true);

	ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
		properties,
		[=] (ObjectDeserializer::ObjectDeserializationArgs deserializeArgs)
		{
			ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
				this->entity,
				deserializeArgs.gameObject,
				ObjectEvents::SpawnMethod::Below,
				ObjectEvents::PositionMode::Discard
			));

			deserializeArgs.gameObject->setPosition(this->entity->getPosition());
			this->helperRef = dynamic_cast<Scrappy*>(deserializeArgs.gameObject);
		}
	);

	this->platformerEntityDeserializer->deserialize(&args);
}
