#ifndef SPRITEREF_H
#define SPRITEREF_H

#include "objectref.h"

namespace SpriterEngine
{

	class TransformProcessor;

	class SpriteRef : public ObjectRef
	{
	public:
		SpriteRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey, int initialFileId, bool initialUseDefaultPivot);

	private:
		ObjectRefInstance *getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance) override;

		int fileId;
		bool useDefaultPivot;
	};

}

#endif // SPRITEREF_H
