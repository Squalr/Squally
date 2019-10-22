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
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/ScrappyBehaviorGroup.h"
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
	this->buildAttachedBehaviorMap();

	this->listenForStateWrite(StateKeys::CurrentHelper, [=](Value value)
	{
		this->spawnHelper(value.asString());
	});
}

void HelperManagerBehavior::spawnHelper(std::string helperName)
{
	ValueMap properties = ValueMap();

	SaveManager::saveProfileData(SaveKeys::SaveKeyHelperName, Value(helperName));

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
	this->attachedBehaviorMap[Guano::MapKeyGuano] = GuanoBehaviorGroup::MapKeyAttachedBehavior;
}
