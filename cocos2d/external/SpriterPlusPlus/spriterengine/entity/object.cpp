#include "object.h"

#include "../global/settings.h"

#include "../override/SPPobjectfactory.h"

#include "../objectinfo/pointobjectinfo.h"
#include "../objectinfo/boneobjectinfo.h"
#include "../objectinfo/boxobjectinfo.h"
#include "../objectinfo/spriteobjectinfo.h"
#include "../objectinfo/entityobjectinfo.h"
#include "../objectinfo/soundobjectinfo.h"
#include "../objectinfo/triggerobjectinfo.h"
#include "../objectinfo/pointinstanceinfo.h"
#include "../objectinfo/boneinstanceinfo.h"
#include "../objectinfo/boxinstanceinfo.h"

#include "../variable/variableinstancenameandidmap.h"

#include "../model/spritermodel.h"

#include "entityinstance.h"
#include "entityinstancedata.h"

namespace SpriterEngine
{

	Object::Object(std::string initialName, int initialId, ObjectType initialObjectType) :
		name(initialName),
		objectId(initialId),
		objectType(initialObjectType)
	{
	}

	std::string Object::getName()
	{
		return name;
	}

	int Object::getId()
	{
		return objectId;
	}

	Object::ObjectType Object::getType()
	{
		return objectType;
	}

	void Object::addInitializationId(int newId)
	{
		for (auto& it : initializationIds)
		{
			if (it == newId)
			{
				return;
			}
		}
		initializationIds.push_back(newId);
	}

	void Object::setSize(point newSize)
	{
		size = newSize;
	}

	UniversalObjectInterface *Object::getNewObjectInfoInstance()
	{
		switch (objectType)
		{
		case OBJECTTYPE_POINT:
			return new PointObjectInfo();

		case OBJECTTYPE_BONE:
			return new BoneObjectInfo();

		case OBJECTTYPE_BOX:
			return new BoxObjectInfo();

		case OBJECTTYPE_SPRITE:
			return new SpriteObjectInfo();

		case OBJECTTYPE_ENTITY:
			return new EntityObjectInfo();

		case OBJECTTYPE_SOUND:
			return new SoundObjectInfo();

		case OBJECTTYPE_TRIGGER:
			return new TriggerObjectInfo();

		default:
			Settings::error("Object::getNewObjectInfoInstance - invalid object type");
			return 0;
		}
	}

	void Object::addObjectInstanceToEntityInstanceData(SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory)
	{
		switch (objectType)
		{
		case OBJECTTYPE_SPRITE:
			if (objectFactory)
			{
				entityInstanceData->setObjectInstance(objectId, name, objectFactory->newSpriteObjectinfo());
			}
			else
			{
				entityInstanceData->setObjectInstance(objectId, name, new SpriteObjectInfo());
			}
			break;

		case OBJECTTYPE_POINT:
			if (objectFactory)
			{
				entityInstanceData->setObjectInstance(objectId, name, objectFactory->newPointInstanceInfo());
			}
			else
			{
				entityInstanceData->setObjectInstance(objectId, name, new PointInstanceInfo());
			}
			break;

		case OBJECTTYPE_BONE:
			if (objectFactory)
			{
				entityInstanceData->setObjectInstance(objectId, name, objectFactory->newBoneInstanceInfo(size));
			}
			else
			{
				entityInstanceData->setObjectInstance(objectId, name, new BoneInstanceInfo(size));
			}
			break;

		case OBJECTTYPE_BOX:
			if (objectFactory)
			{
				entityInstanceData->setObjectInstance(objectId, name, objectFactory->newBoxInstanceInfo(size));
			}
			else
			{
				entityInstanceData->setObjectInstance(objectId, name, new BoxInstanceInfo(size));
			}
			break;

		case OBJECTTYPE_ENTITY:
			entityInstanceData->setObjectInstance(objectId, name, model->getNewEntityInstance(&initializationIds));
			break;

		case OBJECTTYPE_SOUND:
			if (initializationIds.size())
			{
				entityInstanceData->setSoundInstance(objectId, name, entityInstance->getFile(initializationIds.back()));
			}
			break;

		case OBJECTTYPE_TRIGGER:
			if (objectFactory)
			{
				entityInstanceData->setTriggerInstance(objectId, name, objectFactory->newTriggerObjectInfo(name));
			}
			else
			{
				entityInstanceData->setTriggerInstance(objectId, name);
			}
			break;

		default:
			entityInstanceData->setObjectInstance(objectId, name, getNewObjectInfoInstance());
			break;
		}
	}

}
