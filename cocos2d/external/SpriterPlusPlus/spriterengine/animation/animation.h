#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "../timeline/timeline.h"

#include "mainlinekey.h"
#include "mainlinekeyinstance.h"

namespace SpriterEngine
{

	class TimelineInstance;
	class VariableTimeline;
	class TimelineKey;

	typedef std::vector<MainlineKey*> MainlineKeyVector;
	typedef std::vector<Timeline*> TimelineVector;
	typedef std::map<int,Timeline*> TimelineMap;
	typedef std::map<int,TimelineMap> Timeline2DMap;
	typedef std::vector<MainlineKeyInstance*> MainlineKeyInstanceVector;
	typedef std::vector<TimelineInstance*> TimelineInstanceVector;
	
	class Animation
	{
	public:
		Animation(std::string initialName, real initialAnimationLength, bool initialLooping);
		~Animation();

		std::string getName();
		real getLength();
		bool getIsLooping();

		void setupAnimationInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, MainlineKeyInstanceVector *mainlineKeyInstances, TimelineInstanceVector *timelineInstances, real *length, bool *looping);

		MainlineKey *pushBackMainlineKey(TimeInfo *initialTimeInfo);

		Timeline *pushBackObjectTimeline(int objectId);

		Timeline *setVariableTimeline(int objectId, int variableId);
		Timeline *pushBackTagTimeline(int objectId);
		Timeline *pushBackSoundTimeline(int objectId);
		Timeline *pushBackTriggerTimeline(int objectId);

		int getObjectIdFromTimelineIndex(int timelineIndex);
		TimelineKey *getObjectTimelineKey(int timelineIndex, int keyIndex);

	private:
		std::string name;

		MainlineKeyVector mainlineKeys;

		TimelineVector objectTimelines;

		Timeline2DMap variableTimelines;
		TimelineVector tagTimelines;
		TimelineVector soundTimelines;
		TimelineVector triggerTimelines;

		real animationLength;
		bool isLooping;
	};

}

#endif // ANIMATION_H
