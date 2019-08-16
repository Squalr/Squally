#include "FlyBotManagerBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerEntityDeserializer.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/FlyBot.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Helpers/FlyBot/FlyBotBehaviorGroup.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"


using namespace cocos2d;

const std::string FlyBotManagerBehavior::MapKeyAttachedBehavior = "flybot-manager";

FlyBotManagerBehavior* FlyBotManagerBehavior::create(GameObject* owner)
{
	FlyBotManagerBehavior* instance = new FlyBotManagerBehavior(owner);

	instance->autorelease();

	return instance;
}

FlyBotManagerBehavior::FlyBotManagerBehavior(GameObject* owner) : super(owner)
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

FlyBotManagerBehavior::~FlyBotManagerBehavior()
{
}

void FlyBotManagerBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforePlatformerMapChange, [=](EventCustom* eventCustom)
	{
		// Since FlyBot is found on the first map, this is a good way to ensure there are no sequence breaks
		SaveManager::softSaveProfileData(SaveKeys::SaveKeyFlyBotFound, Value(true));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HelperEvents::EventFindFlyBot, [=](EventCustom* eventCustom)
	{
		SaveManager::softSaveProfileData(SaveKeys::SaveKeyFlyBotFound, Value(true));
		this->spawnFlyBot();
	}));

	if (SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyFlyBotFound, Value(false)).asBool())
	{
		this->spawnFlyBot();
	}
}

void FlyBotManagerBehavior::spawnFlyBot()
{
	ValueMap properties = ValueMap();

	properties[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
	properties[GameObject::MapKeyName] = Value(FlyBot::MapKeyFlyBot);
	properties[GameObject::MapKeyAttachedBehavior] = Value(FlyBotBehaviorGroup::MapKeyAttachedBehavior);
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
			this->helperRef = dynamic_cast<FlyBot*>(deserializeArgs.gameObject);
		}
	);

	this->platformerEntityDeserializer->deserialize(&args);
}
