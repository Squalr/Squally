#include "RescueGuanoLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/ChatWithGuano.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/KillTheTroll.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/RescueGuano.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/TrollInTheDungeon.h"

using namespace cocos2d;

const std::string RescueGuanoLine::MapKeyQuestLine = "rescue-guano";

RescueGuanoLine* RescueGuanoLine::create()
{
	RescueGuanoLine* instance = new RescueGuanoLine();

	instance->autorelease();

	return instance;
}

RescueGuanoLine::RescueGuanoLine() : super(RescueGuanoLine::MapKeyQuestLine, {
	QuestData(TrollInTheDungeon::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return TrollInTheDungeon::create(owner, questLine); }),
	QuestData(KillTheTroll::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine) { return KillTheTroll::create(owner, questLine); }),
	QuestData(ChatWithGuano::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine) { return ChatWithGuano::create(owner, questLine); }),
	QuestData(RescueGuano::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine) { return RescueGuano::create(owner, questLine); }),
})
{
}

RescueGuanoLine::~RescueGuanoLine()
{
}
