#include "RescueGuanoLine.h"

#include "Engine/Quests/QuestTask.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/ChatWithGuano.h"
#include "Scenes/Platformer/Quests/EndianForest/RescueGuano/PersuadeGuard.h"
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
	QuestData(TrollInTheDungeon::MapKeyQuest, true, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return TrollInTheDungeon::create(owner, questLine, questTag); }),
	QuestData(PersuadeGuard::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return PersuadeGuard::create(owner, questLine, questTag); }),
	QuestData(ChatWithGuano::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return ChatWithGuano::create(owner, questLine, questTag); }),
	QuestData(RescueGuano::MapKeyQuest, false, [=](GameObject* owner, QuestLine* questLine, std::string questTag) { return RescueGuano::create(owner, questLine, questTag); }),
})
{
}

RescueGuanoLine::~RescueGuanoLine()
{
}
