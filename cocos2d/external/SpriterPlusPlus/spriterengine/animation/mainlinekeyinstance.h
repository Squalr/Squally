#ifndef MAINLINEKEYINSTANCE_H
#define MAINLINEKEYINSTANCE_H

#include <vector>
#include <map>

#include "../global/global.h"

#include "../objectref/transformprocessor.h"

namespace SpriterEngine
{

	class ObjectRefInstance;

	typedef std::vector<ObjectRefInstance*> RefInstanceVector;

	typedef std::vector<UniversalObjectInterface*> ObjectInterfaceVector;

	class EntityInstance;
	class EntityInstanceData;
	class MainlineKey;
	class TimeInfo;
	class MainlineKeyInstance
	{
	public:
		MainlineKeyInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, MainlineKey *mainlineKey);
		~MainlineKeyInstance();

		real process(real currentTime, ObjectInterfaceVector **instanceZOrder);

		real processRefKeys(real currentTime);

		void blendRefKeys(real currentTime, real blendRatio);
		void setZOrder(ObjectInterfaceVector ** instanceZOrder);
		void processRefTransforms();

		real getTime();
		real getNextTime();
		bool timeInRange(real timeToCheck);

	private:
		RefInstanceVector refs;
		ObjectInterfaceVector zOrder;
		TimeInfo *timeInfo;
	};

}

#endif // MAINLINEKEYINSTANCE_H
