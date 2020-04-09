#include "FindElrielLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/FindElrielTelomere.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/ReturnToQueen.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/SneakPastLycan.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToElriel.h"
#include "Scenes/Platformer/Quests/EndianForest/FindElriel/TalkToGrogg.h"
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
	QuestData(SneakPastLycan::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return SneakPastLycan::create(owner, questLine); }),
	QuestData(TownArrival::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TownArrival::create(owner, questLine); }),
	QuestData(TownExitBlocked::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TownExitBlocked::create(owner, questLine); }),
	QuestData(TalkToQueen::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToQueen::create(owner, questLine); }),
	QuestData(TalkToChiron::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToChiron::create(owner, questLine); }),
	QuestData(TalkToGrogg::MapKeyQuest, true, [](GameObject* owner, QuestLine* questLine) { return TalkToGrogg::create(owner, questLine); }),
	QuestData(TalkToElriel::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return TalkToElriel::create(owner, questLine); }),
	QuestData(ReturnToQueen::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return ReturnToQueen::create(owner, questLine); }),
	QuestData(FindElrielTelomere::MapKeyQuest, false, [](GameObject* owner, QuestLine* questLine) { return FindElrielTelomere::create(owner, questLine); }),
})
{
}

FindElrielLine::~FindElrielLine()
{
}

QuestLine* FindElrielLine::clone()
{
	return FindElrielLine::create();
}
