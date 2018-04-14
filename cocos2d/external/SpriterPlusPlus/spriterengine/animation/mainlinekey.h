#ifndef MAINLINEKEY_H
#define MAINLINEKEY_H

#include <vector>

#include "../global/global.h"

namespace SpriterEngine
{

	class ObjectRef;
	class ObjectRefInstance;
	class UniversalObjectInterface;
	class EntityInstance;
	class EntityInstanceData;
	class TimelineKey;
	class TimeInfo;

	typedef std::vector<ObjectRef*> RefVector;
	typedef std::vector<ObjectRefInstance*> RefInstanceVector;

	typedef std::vector<UniversalObjectInterface*> ObjectInterfaceVector;

	class MainlineKey
	{
	public:
		MainlineKey(TimeInfo *initialTimeInfo);
		~MainlineKey();

		void setupRefInstancesAndTimeInfo(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, RefInstanceVector *refInstances, ObjectInterfaceVector *instanceZOrder, TimeInfo *&instanceTimeInfo);

		void pushBackBoneRef(ObjectRef *ref);
		void pushBackZOrderRef(ObjectRef *ref);

		real getTime();

	private:
		TimeInfo *timeInfo;
		RefVector boneRefs;
		RefVector zOrderRefs;
	};

}

#endif // MAINLINEKEY_H
