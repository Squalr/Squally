#include "EntityPickPocketBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/UI/Mouse.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/PocketPools/PocketPoolDeserializer.h"
#include "Menus/CursorSets.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityPickPocketBehavior::MapKeyAttachedBehavior = "pick-pocket";
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
	if (this->entity->getAttachedBehavior<EntitySelectionBehavior>() == nullptr)
	{
		this->entity->attachBehavior(EntitySelectionBehavior::create(this->entity));
	}

	this->entity->watchForAttachedBehavior<EntitySelectionBehavior>([=](EntitySelectionBehavior* selectionBehavior)
	{
		selectionBehavior->setEntityClickCallbacks([=]()
		{
			
		},
		[=]()
		{
			Mouse::getInstance()->setActiveCursorSet(CursorSets::PickPocket);
		},
		[=]()
		{
			Mouse::getInstance()->setActiveCursorSet(CursorSets::Default);
		});
	});

	ValueMap valueMap = ValueMap();

	valueMap[GameObject::MapKeyType] = PocketPoolDeserializer::MapKeyTypePocketPool;
	valueMap[GameObject::MapKeyName] = this->entity->getPropertyOrDefault(EntityPickPocketBehavior::MapKeyPocketPool, Value("")).asString();

	ObjectDeserializer::ObjectDeserializationRequestArgs deserializeArgs = ObjectDeserializer::ObjectDeserializationRequestArgs(valueMap, [=](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		MinMaxPool* pocketPool = static_cast<MinMaxPool*>(args.gameObject);

		this->addChild(pocketPool);
	});
	
	this->pocketPoolDeserializer->deserialize(&deserializeArgs);
}
