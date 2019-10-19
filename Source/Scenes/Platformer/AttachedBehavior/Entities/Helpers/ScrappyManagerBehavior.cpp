#include "ScrappyManagerBehavior.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/ScrappyBehaviorGroup.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"


using namespace cocos2d;

const std::string ScrappyManagerBehavior::MapKeyAttachedBehavior = "scrappy-manager";

ScrappyManagerBehavior* ScrappyManagerBehavior::create(GameObject* owner)
{
	ScrappyManagerBehavior* instance = new ScrappyManagerBehavior(owner);

	instance->autorelease();

	return instance;
}

ScrappyManagerBehavior::ScrappyManagerBehavior(GameObject* owner) : super(owner)
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

ScrappyManagerBehavior::~ScrappyManagerBehavior()
{
}

void ScrappyManagerBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforePlatformerMapChange, [=](EventCustom* eventCustom)
	{
		// Since Scrappy is found on the first map, this is a good way to ensure there are no sequence breaks
		SaveManager::softSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HelperEvents::EventFindScrappy, [=](EventCustom* eventCustom)
	{
		SaveManager::softSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
		this->spawnScrappy();
	}));

	if (SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyScrappyFound, Value(false)).asBool())
	{
		this->spawnScrappy();
	}
}

void ScrappyManagerBehavior::spawnScrappy()
{
	ValueMap properties = ValueMap();

	properties[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
	properties[GameObject::MapKeyName] = Value(Scrappy::MapKeyScrappy);
	properties[GameObject::MapKeyAttachedBehavior] = Value(ScrappyBehaviorGroup::MapKeyAttachedBehavior);
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
