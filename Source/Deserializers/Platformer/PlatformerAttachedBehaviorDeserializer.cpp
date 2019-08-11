#include "PlatformerAttachedBehaviorDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/AttachedBehavior/PlatformerAttachedBehavior.h"

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
	this->attachedBehaviorDeserializers[EntityBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)EntityBehaviorGroup::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[EntityCollisionBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)EntityCollisionBehaviorGroup::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[NpcBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)NpcBehaviorGroup::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[NpcCollisionBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)NpcCollisionBehavior::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyBehaviorGroup::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyBehaviorGroup::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyCollisionBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyCollisionBehavior::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyOutOfCombatAttackBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyOutOfCombatAttackBehavior::create(owner, attachedBehaviorArgs); };
	this->attachedBehaviorDeserializers[SquallyMovementBehavior::MapKeyAttachedBehavior] = [=](GameObject* owner, std::string attachedBehaviorArgs) { return (AttachedBehavior*)SquallyMovementBehavior::create(owner, attachedBehaviorArgs); };
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
			owner->attachBehavior(attachedBehavior);
		}
	}
}

std::string PlatformerAttachedBehaviorDeserializer::getPropertyDeserializerKey()
{
	return GameObject::MapKeyAttachedBehavior;
}
