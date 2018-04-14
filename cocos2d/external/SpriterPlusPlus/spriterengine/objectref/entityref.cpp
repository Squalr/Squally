#include "entityref.h"

#include "../global/settings.h"

#include "../entity/entityinstance.h"

#include "entityrefinstance.h"


namespace SpriterEngine
{

	EntityRef::EntityRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey, int initialEntityId, int initialAnimationIndex) :
		ObjectRef(initialObjectId, initialParentObjectId, initialKey),
		entityId(initialEntityId),
		animationIndex(initialAnimationIndex)
	{
	}

	ObjectRefInstance *EntityRef::getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance)
	{			
		EntityInstanceData *initialEntity = objectInstance->getEntity(entityId);
		if (!initialEntity)
		{
			Settings::error("EntityRef::getNewSpecializedObjectRefInstance - entity instance data with id - " + std::to_string(entityId) + " not found");
			return 0;
		}
		return new EntityRefInstance(objectInstance, initialParentTransformer, getKey(), initialEntity, initialEntity->getAnimation(animationIndex));
	}

}
