#include "ScrappyManagerBehavior.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

#include "Deserializers/Platformer/PlatformerEntityDeserializer.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Scrappy/ScrappyBehaviorGroup.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string ScrappyManagerBehavior::MapKey = "scrappy-manager";

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
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
	}));

	this->defer([=]()
	{
		this->addEventListenerIgnorePause(EventListenerCustom::create(HelperEvents::EventFindScrappy, [=](EventCustom* eventCustom)
		{
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
			this->spawnScrappy();
		}));

		if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyScrappyFound, Value(false)).asBool())
		{
			this->spawnScrappy();
		}
	});
}

void ScrappyManagerBehavior::onDisable()
{
	super::onDisable();
}

void ScrappyManagerBehavior::spawnScrappy()
{
	ValueMap properties = ValueMap();

	properties[GameObject::MapKeyType] = Value(PlatformerEntityDeserializer::MapKeyTypeEntity);
	properties[GameObject::MapKeyName] = Value(Scrappy::MapKey);
	properties[GameObject::MapKeyComponent] = Value(ScrappyBehaviorGroup::MapKey);
	properties[GameObject::MapKeyFlipX] = Value(true);

	ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
		properties,
		[=] (ObjectDeserializer::ObjectDeserializationArgs deserializeArgs)
		{
			ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
				this->entity,
				deserializeArgs.gameObject,
				SpawnMethod::Below,
				PositionMode::Discard,
				[&]()
				{
				},
				[&]()
				{
				}
			));

			deserializeArgs.gameObject->setPosition3D(this->entity->getPosition3D());
			this->helperRef = dynamic_cast<Scrappy*>(deserializeArgs.gameObject);
		}
	);

	this->platformerEntityDeserializer->deserialize(&args);
}
