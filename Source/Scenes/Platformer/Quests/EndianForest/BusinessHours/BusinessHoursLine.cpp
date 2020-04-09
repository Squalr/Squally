#include "BusinessHoursLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/BusinessHours/BusinessHours.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/ReturnToQueen.h"

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
		QuestData(BusinessHours::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return BusinessHours::create(owner, questLine); }),
	},
	(QuestLine*)FindElrielLine::create(), ReturnToQueen::MapKeyQuest)
{
}

BusinessHoursLine::~BusinessHoursLine()
{
}

QuestLine* BusinessHoursLine::clone()
{
	return BusinessHoursLine::create();
}
