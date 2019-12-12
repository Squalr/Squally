#include "FindElrielLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElriel.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/ReturnToQueen.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToQueen.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToChiron.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TownArrival.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TownExitBlocked.h"

using namespace cocos2d;

const std::string FindElrielLine::MapKeyQuestLine = "find-elriel";

FindElrielLine* FindElrielLine::create()
{
	FindElrielLine* instance = new FindElrielLine();

	instance->autorelease();

	return instance;
}

FindElrielLine::FindElrielLine() : super(FindElrielLine::MapKeyQuestLine, {
	QuestData(TownArrival::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TownArrival::create(owner, questLine, questTag); }),
	QuestData(TownExitBlocked::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TownExitBlocked::create(owner, questLine, questTag); }),
	QuestData(TalkToQueen::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TalkToQueen::create(owner, questLine, questTag); }),
	QuestData(TalkToChiron::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return TalkToChiron::create(owner, questLine, questTag); }),
	QuestData(FindElriel::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return FindElriel::create(owner, questLine, questTag); }),
	QuestData(ReturnToQueen::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine, std::string questTag) { return ReturnToQueen::create(owner, questLine, questTag); }),
})
{
}

FindElrielLine::~FindElrielLine()
{
}
