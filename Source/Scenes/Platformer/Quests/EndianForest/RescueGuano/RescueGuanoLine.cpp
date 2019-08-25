#include "RescueGuanoLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElriel.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TownExitBlocked.h"

using namespace cocos2d;

const std::string RescueGuanoLine::MapKeyQuestLine = "find-elriel";

RescueGuanoLine* RescueGuanoLine::create()
{
	RescueGuanoLine* instance = new RescueGuanoLine();

	instance->autorelease();

	return instance;
}

RescueGuanoLine::RescueGuanoLine() : super(RescueGuanoLine::MapKeyQuestLine, {
	QuestData(TownExitBlocked::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TownExitBlocked::create(owner, questLine, questTag); }),
	QuestData(FindElriel::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return FindElriel::create(owner, questLine, questTag); }),
})
{
}

RescueGuanoLine::~RescueGuanoLine()
{
}
