#include "BusinessHoursLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/BusinessHours/BusinessHours.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielLine.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToElriel.h"

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
		QuestData(BusinessHours::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return BusinessHours::create(owner, questLine); }),
	},
	(QuestLine*)FindElrielLine::create(), TalkToElriel::MapKeyQuest)
{
}

BusinessHoursLine::~BusinessHoursLine()
{
}

QuestLine* BusinessHoursLine::clone()
{
	return BusinessHoursLine::create();
}
