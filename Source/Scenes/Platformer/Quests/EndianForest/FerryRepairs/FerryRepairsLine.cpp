#include "FerryRepairsLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/Intro/MeetScrappy.h"

using namespace cocos2d;

const std::string FerryRepairsLine::MapKeyQuestLine = "ferry-repairs";

FerryRepairsLine* FerryRepairsLine::create()
{
	FerryRepairsLine* instance = new FerryRepairsLine();

	instance->autorelease();

	return instance;
}

FerryRepairsLine::FerryRepairsLine() : super(FerryRepairsLine::MapKeyQuestLine, {
	QuestData(MeetScrappy::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return MeetScrappy::create(owner, questLine, questTag); }),
})
{
}

FerryRepairsLine::~FerryRepairsLine()
{
}
