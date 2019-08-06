#include "PlatformerAttachedBehaviorDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/AttachedBehaviors/PlatformerAttachedBehaviors.h"

using namespace cocos2d;

PlatformerAttachedBehaviorDeserializer* PlatformerAttachedBehaviorDeserializer::create()
{
	PlatformerAttachedBehaviorDeserializer* instance = new PlatformerAttachedBehaviorDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerAttachedBehaviorDeserializer::PlatformerAttachedBehaviorDeserializer() : super()
{
	this->attachedBehaviorDeserializers = std::map<std::string, std::function<AttachedBehavior*(GameObject*, std::string)>>();
	
	this->attachedBehaviorDeserializers[FirstIOUFound::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)FirstIOUFound::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[EntityBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)EntityBehaviors::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[EntityCollisionBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)EntityCollisionBehaviors::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[NpcBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)NpcBehaviors::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[NpcCollisionBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)NpcCollisionBehaviors::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyBehaviors::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyCollisionBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyCollisionBehaviors::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyOutOfCombatAttackBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyOutOfCombatAttackBehaviors::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyMovementBehaviors::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyMovementBehaviors::create(owner, attachedBehaviorArgs); };
}

PlatformerAttachedBehaviorDeserializer::~PlatformerAttachedBehaviorDeserializer()
{
}

void PlatformerAttachedBehaviorDeserializer::deserializeProperties(GameObject* owner, ValueMap properties)
{
	std::string attachedBehaviorName = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyAttachedBehavior, Value("")).asString();
	std::string attachedBehaviorArgs = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyAttachedBehaviorArgs, Value("")).asString();

	if (!attachedBehaviorName.empty())
	{
		AttachedBehavior* attachedBehavior = this->deserialize(AttachedBehaviorDeserializer::AttachedBehaviorDeserializationRequestArgs(owner, attachedBehaviorName, attachedBehaviorArgs));

		if (attachedBehavior != nullptr)
		{
			owner->addChild(attachedBehavior);
		}
	}
}

std::string PlatformerAttachedBehaviorDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyAttachedBehavior;
}
