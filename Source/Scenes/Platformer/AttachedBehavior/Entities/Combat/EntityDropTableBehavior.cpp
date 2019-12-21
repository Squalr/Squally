#include "EntityDropTableBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MinMaxPool.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/ItemPools/DropPools/DropPoolDeserializer.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string EntityDropTableBehavior::MapKeyAttachedBehavior = "drop-table";

EntityDropTableBehavior* EntityDropTableBehavior::create(GameObject* owner)
{
	EntityDropTableBehavior* instance = new EntityDropTableBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityDropTableBehavior::EntityDropTableBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->dropPoolDeserializer = DropPoolDeserializer::create();
	this->dropPool = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->dropPoolDeserializer);
}

EntityDropTableBehavior::~EntityDropTableBehavior()
{
}

void EntityDropTableBehavior::onLoad()
{
}

void EntityDropTableBehavior::setDropTable(std::string dropTable)
{
	if (this->dropPool != nullptr)
	{
		this->removeChild(this->dropPool);
		this->dropPool = nullptr;
	}

	ValueMap valueMap = ValueMap();

	valueMap[GameObject::MapKeyType] = DropPoolDeserializer::MapKeyTypeDropPool;
	valueMap[GameObject::MapKeyName] = dropTable;

	ObjectDeserializer::ObjectDeserializationRequestArgs deserializeArgs = ObjectDeserializer::ObjectDeserializationRequestArgs(valueMap, [=](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		MinMaxPool* dropPool = static_cast<MinMaxPool*>(args.gameObject);

		this->dropPool = dropPool;

		this->addChild(this->dropPool);
	});

	this->dropPoolDeserializer->deserialize(&deserializeArgs);
}

MinMaxPool* EntityDropTableBehavior::getDropPool()
{
	return this->dropPool;
}
