#include "entity.h"
#include "object.h"

#include "../global/settings.h"

#include "../animation/animationinstance.h"

#include "../override/SPPobjectfactory.h"
#include "../model/spritermodel.h"

#include "entityinstance.h"
#include "entityinstancedata.h"

namespace SpriterEngine
{

	Entity::Entity(std::string initialName, int initialId, FileVector *initialFileVector) :
		entityId(initialId),
		name(initialName),
		files(initialFileVector)
	{
	}

	Entity::~Entity()
	{
		for (auto& it : animations)
		{
			delete it;
		}
	}

	int Entity::getId()
	{
		return entityId;
	}

	std::string Entity::getName()
	{
		return name;
	}

	EntityInstance *Entity::getNewEntityInstance(SpriterModel *model, ObjectFactory *objectFactory)
	{
		return new EntityInstance(model, this, this, objectFactory);
	}

	void Entity::setupInstance(SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory)
	{
		setupObjectInstances(model, entityInstance, entityInstanceData, objectFactory);
		setupVariableInstances(entityInstanceData->getVariableInstanceMap(THIS_ENTITY, ""));
		entityInstanceData->setTagInstance(THIS_ENTITY, "");
		setupAnimationInstances(entityInstance, entityInstanceData);
	}

	Object *Entity::setObject(std::string objectName, Object::ObjectType objectType)
	{
		switch (objectType)
		{
		case Object::OBJECTTYPE_SOUND:
			return setSoundObject(objectName);

		case Object::OBJECTTYPE_TRIGGER:
			return setTriggerObject(objectName);

		case Object::OBJECTTYPE_ENTITY:
			return setSubEntityObject(objectName);

		default:
			return setSpatialObject(objectName, objectType);
		}

	}

	Object * Entity::getObject(int objectId)
	{
		auto it = objectIdMap.find(objectId);
		if (it != objectIdMap.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("Entity::getObject - object with id " + std::to_string(objectId) + " not found");
			return 0;
		}
	}

	Variable * Entity::getVariable(int objectId, int variableId)
	{
		if (objectId == THIS_ENTITY)
		{
			return VariableContainer::getVariable(variableId);
		}
		else
		{
			Object *object = getObject(objectId);
			if (object)
			{
				return object->getVariable(variableId);
			}
			else
			{
				Settings::error("Entity::getVariable - object with id " + std::to_string(variableId) + " not found");
				return 0;
			}
		}
	}

	Object * Entity::setSpatialObject(std::string objectName, Object::ObjectType objectType)
	{
		auto it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			int size = objectNameMap.size();
			return objectIdMap[size] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, size, objectType))).first).second);
		}
	}

	Object * Entity::setSoundObject(std::string objectName)
	{
		auto it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			int size = objectNameMap.size();
			return soundIdMap[size] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, size, Object::OBJECTTYPE_SOUND))).first).second);
		}
	}

	Object * Entity::setTriggerObject(std::string objectName)
	{
		auto it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			int size = objectNameMap.size();
			return triggerIdMap[size] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, size, Object::OBJECTTYPE_TRIGGER))).first).second);
		}
	}

	Object * Entity::setSubEntityObject(std::string objectName)
	{
		auto it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			int size = objectNameMap.size();
			return subEntityIdMap[size] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, size, Object::OBJECTTYPE_ENTITY))).first).second);
		}
	}

	CharacterMap *Entity::addCharacterMap(std::string name)
	{
		return &characterMaps[name];
	}

	void Entity::applyCharacterMap(std::string mapName, FileReferenceVector *mappedFiles)
	{
		auto it = characterMaps.find(mapName);
		if (it != characterMaps.end())
		{
			(*it).second.applyCharacterMap(mappedFiles);
		}
		else
		{
			Settings::error("Entity::applyCharacterMap - character map with name \"" + mapName + "\" not found");
		}
	}

	void Entity::removeAllCharacterMaps(FileReferenceVector *mappedFiles)
	{
		auto mappedFileIt = mappedFiles->begin();
		for (auto& it : *files)
		{
			(*mappedFileIt++)->setFile(it);
		}
	}

	Animation *Entity::pushBackAnimation(std::string animationName, real length, bool looping)
	{
		animations.push_back(new Animation(animationName, length, looping));
		return animations.back();
	}

	UniversalObjectInterface *Entity::getNewObjectInfoInstance(int objectId)
	{
		auto it = objectIdMap.find(objectId);
		if (it != objectIdMap.end())
		{
			return (*it).second->getNewObjectInfoInstance();
		}
		else
		{
			Settings::error("Entity::getNewObjectInfoInstance - object with id " + std::to_string(objectId) + " not found");
			return 0;
		}
	}

	void Entity::setupDefaultVariableTimelines()
	{
		for (auto& animIt : animations)
		{
			for (auto& objIt : objectNameMap)
			{
				objIt.second.setupDefaultVariableTimelines(animIt, objIt.second.getId());
			}
			VariableContainer::setupDefaultVariableTimelines(animIt, THIS_ENTITY);
		}
	}

	void Entity::setupAnimationInstances(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData)
	{
		for (auto& it : animations)
		{
			entityInstanceData->pushBackAnimationInstance(it->getName(), new AnimationInstance(entityInstance, entityInstanceData, it));
		}
	}

	void Entity::setupObjectInstance(Object *object, SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory)
	{
		object->addObjectInstanceToEntityInstanceData(model, entityInstance, entityInstanceData, objectFactory);
		object->setupVariableInstances(entityInstanceData->getVariableInstanceMap(object->getId(), object->getName()));
		entityInstanceData->setTagInstance(object->getId(), object->getName());
	}

	void Entity::setupObjectInstances(SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory)
	{
		for (auto& it : objectNameMap)
		{
			setupObjectInstance(&it.second, model, entityInstance, entityInstanceData, objectFactory);
		}
	}

}
