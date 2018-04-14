#ifndef OBJECTREF_H
#define OBJECTREF_H

namespace SpriterEngine
{

	class ObjectRefInstance;
	class EntityInstance;
	class EntityInstanceData;
	class TransformProcessor;
	class TimelineKey;
	class UniversalObjectInterface;

	class ObjectRef
	{
	public:
		ObjectRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey);
		virtual ~ObjectRef() {}

		ObjectRefInstance *getNewObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData);
		int id();

	protected:
		TimelineKey *getKey();

	private:
		virtual ObjectRefInstance *getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance);

		int objectId;
		int parentObjectId;

		TimelineKey *key;
	};

}

#endif // OBJECTREF_H
