#include "EntityPickPocketBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/Mouse.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HelperEvents.h"
#include "Objects/Platformer/ItemPools/PocketPools/PocketPoolDeserializer.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityPickPocketBehavior::MapKey = "pick-pocket";
const std::string EntityPickPocketBehavior::SavePropertyKeyWasPickPocketed = "WAS_PICKPOCKETED";
const std::string EntityPickPocketBehavior::MapKeyPocketPool = "pocket-pool";

EntityPickPocketBehavior* EntityPickPocketBehavior::create(GameObject* owner)
{
	EntityPickPocketBehavior* instance = new EntityPickPocketBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityPickPocketBehavior::EntityPickPocketBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->pocketPoolDeserializer = PocketPoolDeserializer::create();
	this->squally = nullptr;
	this->pocketPool = nullptr;
	this->currentHelperName = "";

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->pocketPoolDeserializer);
}

EntityPickPocketBehavior::~EntityPickPocketBehavior()
{
}

void EntityPickPocketBehavior::onLoad()
{
	// Defer this task since it adds an object during onEnterTransitionDidFinish(), which would otherwise cause a crash
	this->defer([=]()
	{
		if (this->entity->getAttachedBehavior<EntitySelectionBehavior>() == nullptr)
		{
			this->entity->attachBehavior(EntitySelectionBehavior::create(this->entity));
		}

		this->entity->watchForAttachedBehavior<EntitySelectionBehavior>([=](EntitySelectionBehavior* selectionBehavior)
		{
			selectionBehavior->setClickModifier(EventKeyboard::KeyCode::KEY_SHIFT);
			selectionBehavior->setEntityClickCallbacks([=]()
			{
				this->attemptPickPocket();
			},
			[=]()
			{
				if (this->currentHelperName == Guano::MapKey && !this->wasPickPocketed())
				{
					CursorSets::setActiveCursorSet(CursorSets::PickPocket);
				}
			},
			[=]()
			{
				CursorSets::setActiveCursorSet(CursorSets::Default);
			});
		});
	});
	
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		this->currentHelperName = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString();

		this->squally->listenForStateWrite(StateKeys::CurrentHelper, [=](Value value)
		{
			this->currentHelperName = value.asString();
		});
	}, Squally::MapKey);

	ValueMap valueMap = ValueMap();

	valueMap[GameObject::MapKeyType] = PocketPoolDeserializer::MapKeyTypePocketPool;
	valueMap[GameObject::MapKeyName] = this->entity->getPropertyOrDefault(EntityPickPocketBehavior::MapKeyPocketPool, Value("")).asString();

	ObjectDeserializer::ObjectDeserializationRequestArgs deserializeArgs = ObjectDeserializer::ObjectDeserializationRequestArgs(valueMap, [=](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		MinMaxPool* pocketPool = static_cast<MinMaxPool*>(args.gameObject);

		this->pocketPool = pocketPool;

		this->addChild(this->pocketPool);
	});
	
	this->pocketPoolDeserializer->deserialize(&deserializeArgs);
}

void EntityPickPocketBehavior::onDisable()
{
	super::onDisable();
}

void EntityPickPocketBehavior::attemptPickPocket()
{
	if (this->currentHelperName == Guano::MapKey && !this->wasPickPocketed())
	{
		HelperEvents::TriggerRequestPickPocket(HelperEvents::RequestPickPocketArgs(
			this->entity,
			this->pocketPool,
			EntityPickPocketBehavior::SavePropertyKeyWasPickPocketed
		));
	}
}

bool EntityPickPocketBehavior::wasPickPocketed()
{
	return this->entity->getObjectStateOrDefault(EntityPickPocketBehavior::SavePropertyKeyWasPickPocketed, Value(false)).asBool();
}
