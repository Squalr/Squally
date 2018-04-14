#ifndef ENTITYREF_H
#define ENTITYREF_H

#include "objectref.h"

namespace SpriterEngine
{

	class TransformProcessor;

	class EntityRef : public ObjectRef
	{
	public:
		EntityRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey, int initialEntityId, int initialAnimationIndex);

	private:
		ObjectRefInstance *getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance) override;

		int entityId;
		int animationIndex;
	};

}

#endif // ENTITYREF_H
