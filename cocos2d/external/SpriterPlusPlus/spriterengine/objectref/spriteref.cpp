#include "spriteref.h"

#include "../entity/entityinstance.h"

#include "spriterefinstance.h"

namespace SpriterEngine
{

	SpriteRef::SpriteRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey, int initialFileId, bool initialUseDefaultPivot) :
		ObjectRef(initialObjectId, initialParentObjectId, initialKey),
		fileId(initialFileId),
		useDefaultPivot(initialUseDefaultPivot)
	{
	}

	ObjectRefInstance *SpriteRef::getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance)
	{
		return new SpriteRefInstance(objectInstance, initialParentTransformer, getKey(), entityInstance->getFile(fileId), useDefaultPivot);
	}

}
