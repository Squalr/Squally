#include "FerryRepairsLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FerryRepairs/FindSail.h"

using namespace cocos2d;

const std::string FerryRepairsLine::MapKeyQuestLine = "ferry-repairs";

FerryRepairsLine* FerryRepairsLine::create()
{
	FerryRepairsLine* instance = new FerryRepairsLine();

	instance->autorelease();

	return instance;
}

FerryRepairsLine::FerryRepairsLine() : super(FerryRepairsLine::MapKeyQuestLine, {
	QuestData(FindSail::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return FindSail::create(owner, questLine); }),
})
{
}

FerryRepairsLine::~FerryRepairsLine()
{
}
