#include "objectref.h"

#include "../global/settings.h"

#include "../entity/entityinstance.h"

#include "objectrefinstance.h"

namespace SpriterEngine
{

	ObjectRef::ObjectRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey) :
		objectId(initialObjectId),
		parentObjectId(initialParentObjectId),
		key(initialKey)
	{
	}

	ObjectRefInstance *ObjectRef::getNewObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData)
	{
		UniversalObjectInterface *initialResultObject = entityInstanceData->getObjectInstance(objectId);
		if (!initialResultObject)
		{
			Settings::error("ObjectRef::getNewObjectRefInstance - object instance for object id " + std::to_string(objectId) + " not found in entity instance data");
			return 0;
		}
		TransformProcessor *initialParentTransformer = entityInstanceData->getTransformer(parentObjectId);
		if (!initialParentTransformer)
		{
			Settings::error("ObjectRef::getNewObjectRefInstance - transform processor for object id " + std::to_string(parentObjectId) + " not found in entity instance data");
			return 0;
		}
		return getNewSpecializedObjectRefInstance(entityInstance, entityInstanceData, initialParentTransformer, initialResultObject);
	}

	int ObjectRef::id()
	{
		return objectId;
	}

	TimelineKey * ObjectRef::getKey()
	{
		return key;
	}

	ObjectRefInstance *ObjectRef::getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance)
	{
		return new ObjectRefInstance(objectInstance, initialParentTransformer, getKey());
	}

}
