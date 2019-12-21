#include "BusinessHoursLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/BusinessHours/BusinessHours.h"

using namespace cocos2d;

const std::string BusinessHoursLine::MapKeyQuestLine = "business-hours";

BusinessHoursLine* BusinessHoursLine::create()
{
	BusinessHoursLine* instance = new BusinessHoursLine();

	instance->autorelease();

	return instance;
}

BusinessHoursLine::BusinessHoursLine() : super(BusinessHoursLine::MapKeyQuestLine,
	{
		QuestData(BusinessHours::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return BusinessHours::create(owner, questLine, questTag); }),
	},
	(QuestLine*)FindElrielLine::create())
{
}

BusinessHoursLine::~BusinessHoursLine()
{
}
