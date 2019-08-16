#include "HelperManagerBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerEntityDeserializer.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Events/HelperEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Helpers/FlyBot/FlyBotBehaviorGroup.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"


using namespace cocos2d;

const std::string HelperManagerBehavior::MapKeyAttachedBehavior = "entity-helper-manager";

HelperManagerBehavior* HelperManagerBehavior::create(GameObject* owner)
{
	HelperManagerBehavior* instance = new HelperManagerBehavior(owner);

	instance->autorelease();

	return instance;
}

HelperManagerBehavior::HelperManagerBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->platformerEntityDeserializer = PlatformerEntityDeserializer::create();
	this->helperRef = nullptr;
	this->attachedBehaviorMap = std::map<std::string, std::string>();

	this->addChild(this->platformerEntityDeserializer);
}

HelperManagerBehavior::~HelperManagerBehavior()
{
}

void HelperManagerBehavior::onLoad()
{
	this->scheduleUpdate();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HelperEvents::EventChangeHelper, [=](EventCustom* eventCustom)
	{
		HelperEvents::ChangeHelperArgs* args = static_cast<HelperEvents::ChangeHelperArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->spawnHelper(args->helperName);
		}
	}));

	this->buildAttachedBehaviorMap();
	this->spawnHelper(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString());
}

void HelperManagerBehavior::spawnHelper(std::string helperName)
{
	ValueMap properties = ValueMap();

	SaveManager::softSaveProfileData(SaveKeys::SaveKeyHelperName, Value(helperName));

	std::string helperBehavior = this->getHelperAttachedBehavior(helperName);

	if (helperBehavior.empty())
	{
		// Abort -- if no behavior found, not a valid helper
		return;
	}

	properties[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
	properties[GameObject::MapKeyName] = Value(helperName);
	properties[GameObject::MapKeyAttachedBehavior] = Value(helperBehavior);
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
		}
	);

	this->platformerEntityDeserializer->deserialize(&args);
}

std::string HelperManagerBehavior::getHelperAttachedBehavior(std::string helperName)
{
	if (this->attachedBehaviorMap.find(helperName) != this->attachedBehaviorMap.end())
	{
		return this->attachedBehaviorMap[helperName];
	}

	return "";
}

void HelperManagerBehavior::buildAttachedBehaviorMap()
{
}
